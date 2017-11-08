/**
 * @Author: danielb
 * @Date:   2017-07-23T01:44:16+02:00
 * @Last modified by:   daniel_b
 * @Last modified time: 2017-11-08T18:22:54+01:00
 */

#include "Shader.hpp"

Shader::Shader(const std::string &vertex, const std::string &fragment)
{
    _programID = glCreateProgram();

    _vertexID = compile(vertex, GL_VERTEX_SHADER);
    _fragmentID = compile(fragment, GL_FRAGMENT_SHADER);

    glAttachShader(_programID, _vertexID);
    glAttachShader(_programID, _fragmentID);

    glLinkProgram(_programID);

    GLint error = 0;
    glGetProgramiv(_programID, GL_LINK_STATUS, &error);
    if (error != GL_TRUE)
    {
        std::cerr << "Cannot link shader.\n";
        int log_length = 0;
        glGetProgramiv(_programID, GL_INFO_LOG_LENGTH, &log_length);
        std::string VertexShaderErrorMessage;
        VertexShaderErrorMessage.resize(log_length + 1);
		    glGetShaderInfoLog(_programID, log_length, NULL, &VertexShaderErrorMessage[0]);
        std::cerr << VertexShaderErrorMessage << "\n";
        throw std::exception();
    }
}

void                Shader::useProgram()
{
    glUseProgram(_programID);
}

void                Shader::setUniformValue(const glm::mat4 &matrix, const std::string &name)
{
  GLuint id = glGetUniformLocation(_programID, name.c_str());
  glProgramUniformMatrix4fv(_programID, id, 1, GL_FALSE, &matrix[0][0]);
}

void                Shader::setUniformValue(const glm::vec3 &vec, const std::string &name)
{
  GLuint id = glGetUniformLocation(_programID, name.c_str());
  glProgramUniform3fv(_programID, id, 1, &vec[0]);
}

void                Shader::setUniformValue(const int value, const std::string &name)
{
  GLuint id = glGetUniformLocation(_programID, name.c_str());
  glProgramUniform1i(_programID, id, value);
}

void                Shader::setUniformValue(const float value, const std::string &name)
{
  GLuint id = glGetUniformLocation(_programID, name.c_str());
  glProgramUniform1f(_programID, id, value);
}

GLuint              Shader::compile(const std::string &source, GLenum type)
{
    GLuint          id;
    std::ifstream   source_file(source);
    std::string    line;
    std::string     src;

    id = glCreateShader(type);
    while (std::getline(source_file, line))
        src += line + "\n";

    const GLchar *gl_src = src.c_str();
    glShaderSource(id, 1, &gl_src, 0);
    glCompileShader(id);

    GLint compile_error = 0;
    glGetShaderiv(id, GL_COMPILE_STATUS, &compile_error);
    if (compile_error != GL_TRUE)
    {
        std::cerr << "Cannot compile " + source + "\n";
        int log_length = 0;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &log_length);
        std::string VertexShaderErrorMessage;
        VertexShaderErrorMessage.resize(log_length + 1);
		glGetShaderInfoLog(id, log_length, NULL, &VertexShaderErrorMessage[0]);
        std::cerr << VertexShaderErrorMessage << "\n";
        throw std::exception();
    }
    return (id);
}

GLuint  Shader::getProgram()
{
    return (_programID);
}
