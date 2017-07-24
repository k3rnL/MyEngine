/**
 * @Author: danielb
 * @Date:   2017-07-24T01:16:33+02:00
 * @Last modified by:   danielb
 * @Last modified time: 2017-07-24T01:51:06+02:00
 */


#include "Object.hpp"

Object::Object()
{
    _buffer_id = 0;
}

Object::~Object()
{
    if (_buffer_id)
        glDeleteBuffers(_buffer_size, &_buffer_id);
}

void            Object::draw(Shader &shader, const glm::mat4 view)
{
    glm::mat4   transform;

    transform *= glm::translate(position);
    transform *= view;

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, _buffer_id);
    glVertexAttribPointer(
        0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
        3,                  // size
        GL_FLOAT,           // type
        GL_FALSE,           // normalized?
        0,                  // stride
        (void*)0            // array buffer offset
        );

    GLuint MatrixID = glGetUniformLocation(shader.getProgram(), "MVP");
    glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &transform[0][0]);

    // Draw the triangle !
    glDrawArrays(GL_TRIANGLES, 0, 3); // 3 indices starting at 0 -> 1 triangle
    glDisableVertexAttribArray(0);
}
