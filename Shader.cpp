/**
 * @Author: danielb
 * @Date:   2017-07-23T01:44:16+02:00
 * @Last modified by:   daniel_b
 * @Last modified time: 2017-07-25T00:23:32+02:00
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
