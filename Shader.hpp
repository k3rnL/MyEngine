/**
 * @Author: danielb
 * @Date:   2017-07-23T01:38:03+02:00
 * @Last modified by:   danielb
 * @Last modified time: 2017-07-23T05:14:27+02:00
 */

#ifndef SHADER_HPP
#define SHADER_HPP

#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <GL/glew.h>

class Shader
{
public:
    Shader(const std::string &vertex, const std::string &frag);

    GLuint  getProgram();

private:

    GLuint      compile(const std::string &source, GLenum type);

    GLuint      _vertexID;
    GLuint      _fragmentID;
    GLuint      _programID;
};

#endif
