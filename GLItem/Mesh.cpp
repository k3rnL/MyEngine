/**
 * @Author: daniel_b
 * @Date:   2017-08-19T20:26:24+02:00
 * @Last modified by:   daniel_b
 * @Last modified time: 2017-09-20T02:18:55+02:00
 */



#include "GLItem/Mesh.hpp"

using namespace mxe::gl_item;

Mesh::Mesh()
{
  _buffer_vertex_id = GL_INVALID_VALUE;
  _buffer_normal_id = GL_INVALID_VALUE;
  _buffer_uv_id = GL_INVALID_VALUE;
  _buffer_size = 0;
  _nb_vertex = 0;
  _shader = ShaderManager::getInstance().getDefaultShader();

  std::cout << "New Mesh ! \n";

}

Mesh::Mesh(Mesh &mesh)
{
    _buffer_vertex_id = GL_INVALID_VALUE;
    _buffer_normal_id = GL_INVALID_VALUE;
    _buffer_uv_id = GL_INVALID_VALUE;
    _buffer_size = 0;
    _nb_vertex = 0;

    std::cout << "New Mesh ! \n";
    _mesh_indices = mesh._mesh_indices;
    _mesh_normals = mesh._mesh_normals;
    _mesh_uvs = mesh._mesh_uvs;
    _mesh_vertexes = mesh._mesh_vertexes;
    _shader = mesh._shader;
    finish();
}

int     Mesh::getElementCount()
{
    return (_mesh_indices.size());
}

void    Mesh::finish()
{
  ShaderManager::getInstance().useShader(_shader);

  if (_buffer_vertex_id != GL_INVALID_VALUE)
    glDeleteBuffers(1, &_buffer_vertex_id);
  if (_buffer_normal_id != GL_INVALID_VALUE)
    glDeleteBuffers(1, &_buffer_normal_id);
  if (_buffer_uv_id != GL_INVALID_VALUE)
    glDeleteBuffers(1, &_buffer_uv_id);

  glGenBuffers(1, &_buffer_vertex_id);
  glBindBuffer(GL_ARRAY_BUFFER, _buffer_vertex_id);
  glBufferData(GL_ARRAY_BUFFER, sizeof (glm::vec3) * _mesh_vertexes.size() , &_mesh_vertexes[0], GL_STATIC_DRAW);

  glGenBuffers(1, &_buffer_indices_id);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _buffer_indices_id);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof (glm::vec3) * _mesh_indices.size() , &_mesh_indices[0], GL_STATIC_DRAW);

  glGenBuffers(1, &_buffer_normal_id);
  glBindBuffer(GL_ARRAY_BUFFER, _buffer_normal_id);
  glBufferData(GL_ARRAY_BUFFER, sizeof (glm::vec3) * _mesh_normals.size() , &_mesh_normals[0], GL_STATIC_DRAW);

  glGenBuffers(1, &_buffer_uv_id);
  glBindBuffer(GL_ARRAY_BUFFER, _buffer_uv_id);
  glBufferData(GL_ARRAY_BUFFER, sizeof (glm::vec2) * _mesh_uvs.size() , &_mesh_uvs[0], GL_STATIC_DRAW);

  _buffer_size = sizeof (glm::vec3) * _mesh_vertexes.size();

  _nb_vertex = _mesh_vertexes.size();

  std::cout << "Face: " << _mesh_indices.size() / 3 << " Vertex: " << _mesh_vertexes.size() << "\n";
}

void    Mesh::bindToShader()
{
    if (ShaderManager::getInstance().getActualShader() != _shader)
    {
        auto shader = ShaderManager::getInstance().getActualShader();
        ShaderManager::getInstance().useShader(_shader);
        clearGPU();
        _shader = shader;
        finish();
    }

  enableAttribute(_buffer_vertex_id, 0, 3);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _buffer_indices_id);
  enableAttribute(_buffer_normal_id, 1, 3);
  enableAttribute(_buffer_uv_id, 2, 2);
}

void    Mesh::detachFromShader()
{
  glDisableVertexAttribArray(0);
  glDisableVertexAttribArray(1);
  glDisableVertexAttribArray(2);
}

void        Mesh::clearGPU()
{
    if (_buffer_vertex_id != GL_INVALID_VALUE)
      glDeleteBuffers(1, &_buffer_vertex_id);
    if (_buffer_normal_id != GL_INVALID_VALUE)
      glDeleteBuffers(1, &_buffer_normal_id);
    if (_buffer_uv_id != GL_INVALID_VALUE)
      glDeleteBuffers(1, &_buffer_uv_id);
}

void    Mesh::addAll(const glm::vec3 &vertex, const glm::vec3 &normal, const glm::vec2 &uv)
{
  _mesh_vertexes.push_back(vertex);
  _mesh_normals.push_back(normal);
  _mesh_uvs.push_back(uv);
}

size_t    Mesh::addVertex(const glm::vec3 &vertex)
{
  _mesh_vertexes.push_back(vertex);
  return (_mesh_vertexes.size() - 1);
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
    _mesh_indices.push_back(indices.x);
    _mesh_indices.push_back(indices.y);
    _mesh_indices.push_back(indices.z);
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

std::vector<unsigned int> &Mesh::getIndices() {
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
  glEnableVertexAttribArray(attr);
  glBindBuffer(buffer_type, buffer);
  glVertexAttribPointer(
      attr,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
      size,                  // size
      GL_FLOAT,           // type
      GL_FALSE,           // normalized?
      0,                  // stride
      (void*)0            // array buffer offset
      );
}
