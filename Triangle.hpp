/**
 * @Author: danielb
 * @Date:   2017-07-23T04:58:34+02:00
 * @Last modified by:   danielb
 * @Last modified time: 2017-07-23T05:10:09+02:00
 */



#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Shader.hpp"

class Triangle
{
public:
    Triangle(const glm::vec3 &v1, const glm::vec3 &v2, const glm::vec3 &v3);

    void    draw(Shader &shader, const glm::mat4 view);

    glm::vec3 position;
private:
    GLuint  _buffer_id;
};

#endif
