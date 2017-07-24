/**
 * @Author: danielb
 * @Date:   2017-07-23T05:03:50+02:00
 * @Last modified by:   danielb
 * @Last modified time: 2017-07-24T02:03:29+02:00
 */



#include "Triangle.hpp"

using namespace mxe::scene::object;

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

    _buffer_size = sizeof (GLfloat) * 9;
}
