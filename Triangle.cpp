/**
 * @Author: danielb
 * @Date:   2017-07-23T05:03:50+02:00
 * @Last modified by:   daniel_b
 * @Last modified time: 2017-07-31T04:33:30+02:00
 */



#include "Triangle.hpp"

using namespace mxe::scene::object;

Triangle::Triangle(const glm::vec3 &v1, const glm::vec3 &v2, const glm::vec3 &v3) :
    _p1(v1), _p2(v2), _p3(v3)
{
    GLfloat buffer_data[] = {
        v1.x, v1.y, v1.z,
        v2.x, v2.y, v2.z,
        v3.x, v3.y, v3.z,
    };

    glGenBuffers(1, &_buffer_vertex_id);
    glBindBuffer(GL_ARRAY_BUFFER, _buffer_vertex_id);
    glBufferData(GL_ARRAY_BUFFER, sizeof (GLfloat) * 9, buffer_data, GL_STATIC_DRAW);

    glm::vec3 n = glm::normalize(v1 * v2);

    GLfloat normals[] = {
      n.x, n.y, n.z,
      n.x, n.y, n.z,
      n.x, n.y, n.z
    };

    glGenBuffers(1, &_buffer_normal_id);
    glBindBuffer(GL_ARRAY_BUFFER, _buffer_normal_id);
    glBufferData(GL_ARRAY_BUFFER, sizeof (GLfloat) * 9, normals, GL_STATIC_DRAW);

    _buffer_size = sizeof (GLfloat) * 9;

    _nb_vertex = 3;

    _material.setColor(0.5, 0., 1.);
    _material.applyMaterial(); // Also call glUseProgram()

}

mxe::scene::INode           *Triangle::clone()
{
    mxe::scene::INode       *node = new Triangle(_p1, _p2, _p3);

    return (node);
}
