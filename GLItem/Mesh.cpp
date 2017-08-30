/**
 * @Author: daniel_b
 * @Date:   2017-08-19T20:26:24+02:00
 * @Last modified by:   daniel_b
 * @Last modified time: 2017-08-30T05:16:48+02:00
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

  std::cout << "New Mesh ! \n";

}

void    Mesh::finish()
{
  if (_buffer_vertex_id != GL_INVALID_VALUE)
    glDeleteBuffers(1, &_buffer_vertex_id);
  if (_buffer_normal_id != GL_INVALID_VALUE)
    glDeleteBuffers(1, &_buffer_normal_id);
  if (_buffer_uv_id != GL_INVALID_VALUE)
    glDeleteBuffers(1, &_buffer_uv_id);

  glGenBuffers(1, &_buffer_vertex_id);
  glBindBuffer(GL_ARRAY_BUFFER, _buffer_vertex_id);
  glBufferData(GL_ARRAY_BUFFER, sizeof (glm::vec3) * _mesh_vertexes.size() , &_mesh_vertexes[0], GL_STATIC_DRAW);

  glGenBuffers(1, &_buffer_normal_id);
  glBindBuffer(GL_ARRAY_BUFFER, _buffer_normal_id);
  glBufferData(GL_ARRAY_BUFFER, sizeof (glm::vec3) * _mesh_normals.size() , &_mesh_normals[0], GL_STATIC_DRAW);

  glGenBuffers(1, &_buffer_uv_id);
  glBindBuffer(GL_ARRAY_BUFFER, _buffer_uv_id);
  glBufferData(GL_ARRAY_BUFFER, sizeof (glm::vec2) * _mesh_uvs.size() , &_mesh_uvs[0], GL_STATIC_DRAW);

  _buffer_size = sizeof (glm::vec3) * _mesh_vertexes.size();

  _nb_vertex = _mesh_vertexes.size();
}

void    Mesh::bindToShader()
{
  enableAttribute(_buffer_vertex_id, 0, 3);
  enableAttribute(_buffer_normal_id, 1, 3);
  enableAttribute(_buffer_uv_id, 2, 2);
}

void    Mesh::detachFromShader()
{
  glDisableVertexAttribArray(0);
  glDisableVertexAttribArray(1);
  glDisableVertexAttribArray(2);
}

void    Mesh::addAll(const glm::vec3 &vertex, const glm::vec3 &normal, const glm::vec2 &uv)
{
  _mesh_vertexes.push_back(vertex);
  _mesh_normals.push_back(normal);
  _mesh_uvs.push_back(uv);
}

void    Mesh::addVertex(const glm::vec3 &vertex)
{
  _mesh_vertexes.push_back(vertex);
}

void    Mesh::addNormal(const glm::vec3 &normal)
{
  _mesh_normals.push_back(normal);
}

void    Mesh::addUV(const glm::vec2 &uv)
{
  _mesh_uvs.push_back(uv);
}

void    Mesh::enableAttribute(GLuint buffer, GLuint attr, GLuint size)
{
  glEnableVertexAttribArray(attr);
  glBindBuffer(GL_ARRAY_BUFFER, buffer);
  glVertexAttribPointer(
      attr,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
      size,                  // size
      GL_FLOAT,           // type
      GL_FALSE,           // normalized?
      0,                  // stride
      (void*)0            // array buffer offset
      );
}
