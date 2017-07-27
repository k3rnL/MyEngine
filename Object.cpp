/**
 * @Author: danielb
 * @Date:   2017-07-24T01:16:33+02:00
 * @Last modified by:   daniel_b
 * @Last modified time: 2017-07-27T05:02:06+02:00
 */


#include "Object.hpp"

using namespace mxe::scene::object;

Object::Object()
{
    _buffer_vertex_id = 0;
    _buffer_normal_id = 0;
}

Object::~Object()
{
    if (_buffer_vertex_id)
        glDeleteBuffers(_buffer_size, &_buffer_vertex_id);
      if (_buffer_normal_id)
          glDeleteBuffers(_buffer_size, &_buffer_normal_id);

}

void            Object::draw(const glm::mat4 &projection, const glm::mat4 &view)
{
    glm::mat4   transform;
    glm::quat   quat(rotation);

    transform = glm::translate(position) * glm::toMat4(quat);

    glUseProgram(_material.getShader().getProgram());
    // _material.applyMaterial(); // Also call glUseProgram()

    enableAttribute(_buffer_vertex_id, 0);
    enableAttribute(_buffer_normal_id, 1);

    _material.getShader().setUniformMatrix(projection, "projection");
    _material.getShader().setUniformMatrix(view, "view");
    _material.getShader().setUniformMatrix(transform, "model_view");

    GLuint uniform_id;

    glm::vec3 tmp2(10, 10, 10);
    uniform_id = glGetUniformLocation(_material.getShader().getProgram(), "light_pos");
    glUniform3fv(uniform_id, 1, &tmp2[0]);

    // Draw the triangle !
    glDrawArrays(GL_TRIANGLES, 0, _nb_vertex); // 3 indices starting at 0 -> 1 triangle
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
}

void    Object::enableAttribute(GLuint buffer, GLuint attr)
{
  glEnableVertexAttribArray(attr);
  glBindBuffer(GL_ARRAY_BUFFER, buffer);
  glVertexAttribPointer(
      attr,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
      3,                  // size
      GL_FLOAT,           // type
      GL_FALSE,           // normalized?
      0,                  // stride
      (void*)0            // array buffer offset
      );
}
