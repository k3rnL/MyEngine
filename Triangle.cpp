/**
 * @Author: danielb
 * @Date:   2017-07-23T05:03:50+02:00
 * @Last modified by:   danielb
 * @Last modified time: 2017-07-23T05:12:44+02:00
 */



#include "Triangle.hpp"

Triangle::Triangle(const glm::vec3 &v1, const glm::vec3 &v2, const glm::vec3 &v3)
{
    GLfloat buffer_data[] = {
        v1.x, v1.y, v1.z,
        v2.x, v2.y, v2.z,
        v3.x, v3.y, v3.z,
    };

    glGenBuffers(1, &_buffer_id);
    glBindBuffer(GL_ARRAY_BUFFER, _buffer_id);
    glBufferData(GL_ARRAY_BUFFER, sizeof (GLfloat) * 9, buffer_data, GL_STATIC_DRAW);
}

void            Triangle::draw(Shader &shader, const glm::mat4 view)
{
    glm::mat4   transform(1.0);

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
