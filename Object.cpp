/**
 * @Author: danielb
 * @Date:   2017-07-24T01:16:33+02:00
 * @Last modified by:   daniel_b
 * @Last modified time: 2017-09-20T15:29:56+02:00
 */


#include "Object.hpp"

using namespace mxe::scene::object;

Object::Object()
{
    _buffer_vertex_id = 0;
    _buffer_normal_id = 0;
    _buffer_uv_id = 0;
    _material = std::make_shared<Material>();
    _mesh = 0;
}

Object::~Object()
{
    if (_buffer_vertex_id)
        glDeleteBuffers(_buffer_size, &_buffer_vertex_id);
    if (_buffer_normal_id)
        glDeleteBuffers(_buffer_size, &_buffer_normal_id);
}

mxe::scene::INode       *Object::clone()
{
    Object           *node = new Object();

    node->_scale = _scale;
    node->_mesh = this->_mesh;
    node->_material = _material;
    return (node);
}

void            Object::setPosition(const glm::vec3 &position)
{
    _position = position;
}

void                Object::draw(renderer::ObjectsToDrawCallback &callback,
                                 const glm::mat4 &transform)
{
    glm::mat4   node_transform;
    glm::quat   quat(_rotation);

    node_transform = transform * glm::translate(_position) * glm::scale(_scale) * glm::toMat4(quat);
    callback.addObject(_material, _mesh, node_transform);

    for (auto child : childs)
    {
        child->draw(callback, node_transform);
    }
}

// void            Object::draw(ShaderManager &shaders, const glm::mat4 &projection, const glm::mat4 &view, const glm::mat4 &parent_transform, const glm::vec3 &cam_pos)
// {
//     glm::mat4   transform;
//     glm::quat   quat(_rotation);
//
//     transform = parent_transform * glm::translate(_position) * glm::toMat4(quat);
//
//     shaders.useDefaultProgram();
//     // glUseProgram(_material->getShader().getProgram());
//     _material->applyMaterial(shaders.getActualShader());
//
//     // enableAttribute(_buffer_vertex_id, 0, 3);
//     // enableAttribute(_buffer_normal_id, 1, 3);
//     // enableAttribute(_buffer_uv_id, 2, 2);
//     _mesh->bindToShader();
//
//     // _material->getShader().setUniformValue(projection, "projection");
//     // _material->getShader().setUniformValue(view, "view");
//     shaders.getActualShader()->setUniformValue(transform, "model_view");
//     shaders.getActualShader()->setUniformValue(glm::toMat4(quat), "model_rotation");
//
//
//     // _material.getShader().setUniformVertex(cam_pos, "camera_position");
//     // Draw the triangle !
//     glDrawArrays(GL_TRIANGLES, 0, _mesh->_nb_vertex); // 3 indices starting at 0 -> 1 triangle
//     // glDisableVertexAttribArray(0);
//     // glDisableVertexAttribArray(1);
//     // glDisableVertexAttribArray(2);
//     _mesh->detachFromShader();
//
//     // INode::draw(shaders, projection, view, parent_transform, cam_pos);
// }

std::shared_ptr<Material>    Object::getMaterial()
{
    return (_material);
}

void    Object::applyMaterial(std::shared_ptr<Material> mat)
{
  _material = mat;
}

void    Object::enableAttribute(GLuint buffer, GLuint attr, GLuint size)
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
