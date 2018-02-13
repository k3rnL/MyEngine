/**
 * @Author: daniel_b
 * @Date:   2017-08-19T20:26:24+02:00
 * @Last modified by:
 * @Last modified time: 2018-01-25T23:12:10+01:00
 */



#include "fse/GLItem/Mesh.hpp"

using namespace fse::gl_item;

Mesh::Mesh() : _buffer_indices(Buffer<GLsizei>::ElementBuffer)
{
  _nb_vertex = 0;
  _min = glm::vec3(0);
  _max = glm::vec3(0);
  _shader = ShaderManager::getInstance().getDefaultShader();
}

Mesh::Mesh(Mesh &mesh)
{
    _mesh_indices = mesh._mesh_indices;
    _mesh_normals = mesh._mesh_normals;
    _mesh_tangents = mesh._mesh_tangents;
    _mesh_bitangents = mesh._mesh_bitangents;
    _mesh_uvs = mesh._mesh_uvs;
    _mesh_vertexes = mesh._mesh_vertexes;
    _shader = mesh._shader;
    finish();
}

void    Mesh::smoothNormal()
{
    std::vector<GLsizei> indices = _mesh_indices;

    while (indices.size()) {
        std::list<unsigned int> index_to_use;

        int i = 0;
        while (i < indices.size())
        {
            if (_mesh_vertexes[indices[i]] == _mesh_vertexes[indices[0]]){
                index_to_use.push_back(indices[i]);
                indices.erase(indices.begin() + i);
            }
            else
                i++;
        }

        bool first_pass = true;
        glm::vec3 normal;
        for (unsigned int index : index_to_use)
        {
            if (first_pass) {
                first_pass = false;
                normal = _mesh_normals[index];
            }
            normal = (normal + _mesh_normals[index]) / glm::vec3(2.0);
        }

        for (unsigned int index : index_to_use)
            _mesh_normals[index] = normal;
    }
}

size_t     Mesh::getElementCount()
{
    return (_mesh_indices.size());
}

void    Mesh::genNormals()
{
    _mesh_normals.resize(_mesh_indices.size());
    _mesh_normals.clear();
    for (int i = 0 ; i < _mesh_indices.size() ; i += 3) {
        glm::vec3 v0 = _mesh_vertexes[_mesh_indices[i]];
        glm::vec3 delta1 = _mesh_vertexes[_mesh_indices[i + 1]] - v0;
        glm::vec3 delta2 = _mesh_vertexes[_mesh_indices[i + 2]] - v0;

        glm::vec3 normal = normalize(delta1 * delta2);
        _mesh_normals[_mesh_indices[i]] += normal;
        _mesh_normals[_mesh_indices[i+1]] += normal;
        _mesh_normals[_mesh_indices[i+2]] += normal;
        _mesh_normals[_mesh_indices[i]] = normalize(_mesh_normals[_mesh_indices[i]]);
        _mesh_normals[_mesh_indices[i+1]] = normalize(_mesh_normals[_mesh_indices[i+1]]);
        _mesh_normals[_mesh_indices[i+2]] = normalize(_mesh_normals[_mesh_indices[i+2]]);
    }
}

void    Mesh::genTangentSpace()
{
    _mesh_tangents.clear();
    _mesh_bitangents.clear();
    _mesh_tangents.resize(_mesh_vertexes.size());
    _mesh_bitangents.resize(_mesh_vertexes.size());
    for (int i = 0 ; i < _mesh_indices.size() ; i += 3) {
        glm::vec3 v0 = _mesh_vertexes[_mesh_indices[i]];
        glm::vec3 delta1 = _mesh_vertexes[_mesh_indices[i + 1]] - v0;
        glm::vec3 delta2 = _mesh_vertexes[_mesh_indices[i + 2]] - v0;

        glm::vec2 uv0 = _mesh_uvs[_mesh_indices[i]];
        glm::vec2 deltaUV1 = _mesh_uvs[_mesh_indices[i + 1]] - uv0;
        glm::vec2 deltaUV2 = _mesh_uvs[_mesh_indices[i + 2]] - uv0;

        float r = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV1.y * deltaUV2.x);
        glm::vec3 tangent = glm::normalize((delta1 * deltaUV2.y - delta2 * deltaUV1.y) * r);
        glm::vec3 bitangent = glm::normalize((delta2 * deltaUV1.x - delta1 * deltaUV2.x) * r);
        _mesh_tangents[_mesh_indices[i]] = tangent;
        _mesh_tangents[_mesh_indices[i+1]] = tangent;
        _mesh_tangents[_mesh_indices[i+2]] = tangent;
        _mesh_bitangents[_mesh_indices[i]] = bitangent;
        _mesh_bitangents[_mesh_indices[i+1]] = bitangent;
        _mesh_bitangents[_mesh_indices[i+2]] = bitangent;
    }
}

void    Mesh::finish()
{
    if (_mesh_normals.size() == 0)
        genNormals();
    if (_mesh_tangents.size() == 0)
        genTangentSpace();
        std::cout << "Tangent size " << _mesh_tangents.size() << "\n";

    _buffer_vertex.send(_mesh_vertexes);
    _buffer_tangent.send(_mesh_tangents);
    _buffer_bitangent.send(_mesh_bitangents);
    _buffer_normal.send(_mesh_normals);
    _buffer_indices.send(_mesh_indices);
    _buffer_uv.send(_mesh_uvs);

    _nb_vertex = _mesh_vertexes.size();

    std::cout << "Face: " << _mesh_indices.size() / 3 << " Vertex: " << _mesh_vertexes.size() << "\n";

}

void    Mesh::bindToShader(std::shared_ptr<Shader> shader)
{
  shader->setAttribute(_buffer_vertex, 0, 3);
  shader->setAttribute(_buffer_normal, 1, 3);
  shader->setAttribute(_buffer_uv, 2, 2);
  shader->setAttribute(_buffer_tangent, 3, 3);
  shader->setAttribute(_buffer_bitangent, 4, 3);
  _buffer_indices.bind();
}

void    Mesh::detachFromShader()
{
  glDisableVertexAttribArray(0);
  glDisableVertexAttribArray(1);
  glDisableVertexAttribArray(2);
  glDisableVertexAttribArray(3);
  glDisableVertexAttribArray(4);
}

void        Mesh::clearGPU()
{

}

void    Mesh::addAll(const glm::vec3 &vertex, const glm::vec3 &normal, const glm::vec2 &uv)
{
  _mesh_vertexes.push_back(vertex);
  _mesh_normals.push_back(normal);
  _mesh_uvs.push_back(uv);
}

size_t    Mesh::addVertex(const glm::vec3 &vertex)
{
    if (vertex.x < _min.x)
        _min.x = vertex.x;
    if (vertex.y < _min.y)
        _min.y = vertex.y;
    if (vertex.z < _min.z)
        _min.z = vertex.z;

    if (vertex.x > _max.x)
        _max.x = vertex.x;
    if (vertex.y > _max.y)
        _max.y = vertex.y;
    if (vertex.z > _max.z)
        _max.z = vertex.z;

  _mesh_vertexes.push_back(vertex);
  return (_mesh_vertexes.size() - 1);
}

size_t    Mesh::addTangent(const glm::vec3 &vertex)
{
  _mesh_tangents.push_back(vertex);
  return (_mesh_tangents.size() - 1);
}

size_t    Mesh::addBitangent(const glm::vec3 &vertex)
{
  _mesh_bitangents.push_back(vertex);
  return (_mesh_bitangents.size() - 1);
}

size_t    Mesh::addNormal(const glm::vec3 &normal)
{
  _mesh_normals.push_back(normal);
  return (_mesh_normals.size() - 1);
}

size_t    Mesh::addUV(const glm::vec2 &uv)
{
  _mesh_uvs.push_back(uv);
  return (_mesh_uvs.size() - 1);
}

size_t    Mesh::addFace(const glm::vec3 &indices)
{
    _mesh_indices.push_back((GLsizei) indices.x);
    _mesh_indices.push_back((GLsizei) indices.y);
    _mesh_indices.push_back((GLsizei) indices.z);
    return (_mesh_indices.size() - 3);
}

std::vector<glm::vec3>    &Mesh::getVertexes() {
    return (_mesh_vertexes);
}

std::vector<glm::vec3>    &Mesh::getNormals() {
    return (_mesh_normals);
}

std::vector<glm::vec2>    &Mesh::getUVs() {
    return (_mesh_uvs);
}

std::vector<GLsizei> &Mesh::getIndices() {
    return (_mesh_indices);
}

void    Mesh::clear() {
    _mesh_indices.clear();
    _mesh_normals.clear();
    _mesh_uvs.clear();
    _mesh_vertexes.clear();
}

void    Mesh::enableAttribute(GLuint buffer, GLuint attr, GLuint size, GLint buffer_type)
{
  // glEnableVertexAttribArray(attr);
  // glBindBuffer(buffer_type, buffer);
  // glVertexAttribPointer(
  //     attr,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
  //     size,                  // size
  //     GL_FLOAT,           // type
  //     GL_FALSE,           // normalized?
  //     0,                  // stride
  //     (void*)0            // array buffer offset
  //     );
}
