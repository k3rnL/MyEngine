/**
 * @Author: danielb
 * @Date:   2017-07-24T01:16:33+02:00
 * @Last modified by:   daniel_b
 * @Last modified time: 2017-07-27T03:42:43+02:00
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

    transform = glm::translate(position);

    _material.applyMaterial(); // Also call glUseProgram()

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, _buffer_vertex_id);
    glVertexAttribPointer(
        0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
        3,                  // size
        GL_FLOAT,           // type
        GL_FALSE,           // normalized?
        0,                  // stride
        (void*)0            // array buffer offset
        );

    // std::cout << "Array addres=" << glGetAttribLocation(_material.getShader().getProgram(), "vertex") << "\n";
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, _buffer_normal_id);
    glVertexAttribPointer(
        1,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
        3,       // size
        GL_FLOAT,           // type
        GL_FALSE,           // normalized?
        0,                  // stride
        (void*)0            // array buffer offset
        );

    glm::mat4 tmp(1.);
    glm::mat4 tmp1(1.);

    tmp = transform;

    GLuint uniform_id;

    uniform_id = glGetUniformLocation(_material.getShader().getProgram(), "projection");
    glUniformMatrix4fv(uniform_id, 1, GL_FALSE, &projection[0][0]);

    uniform_id = glGetUniformLocation(_material.getShader().getProgram(), "view");
    glUniformMatrix4fv(uniform_id, 1, GL_FALSE, &view[0][0]);

    uniform_id = glGetUniformLocation(_material.getShader().getProgram(), "model_view");
    glUniformMatrix4fv(uniform_id, 1, GL_FALSE, &transform[0][0]);

    glm::vec3 tmp2(100, 100, 10);

    uniform_id = glGetUniformLocation(_material.getShader().getProgram(), "light_pos");
    glUniform3fv(uniform_id, 1, &tmp2[0]);

    // std::cout << "id=" << MatrixID << "\n";


    // Draw the triangle !
    glDrawArrays(GL_TRIANGLES, 0, _nb_vertex); // 3 indices starting at 0 -> 1 triangle
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
}
