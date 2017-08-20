/**
 * @Author: danielb
 * @Date:   2017-07-23T01:38:03+02:00
 * @Last modified by:   daniel_b
 * @Last modified time: 2017-08-19T18:11:08+02:00
 */

#ifndef SHADER_HPP
#define SHADER_HPP

#include <string>
#include <fstream>
#include <iostream>
#include <vector>

#include <GL/glew.h>
#include <glm/glm.hpp>

class Shader
{
public:
    Shader(const std::string &vertex, const std::string &frag);

    GLuint  getProgram();

    void    setUniformValue(const glm::mat4 &matrix, const std::string &name);
    void    setUniformValue(const glm::vec3 &vec, const std::string &name);
    void    setUniformValue(const int value, const std::string &name);

private:

    GLuint      compile(const std::string &source, GLenum type);

    GLuint      _vertexID;
    GLuint      _fragmentID;
    GLuint      _programID;
};

#endif
