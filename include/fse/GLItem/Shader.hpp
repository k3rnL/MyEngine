/**
 * @Author: danielb
 * @Date:   2017-07-23T01:38:03+02:00
 * @Last modified by:   daniel_b
 * @Last modified time: 2017-12-16T01:54:14+01:00
 */

#ifndef SHADER_HPP
#define SHADER_HPP

#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <map>

#include <GL/glew.h>
#include <glm/glm.hpp>

#include <fse/GLItem/Buffer.hpp>

namespace fse {
    namespace gl_item {

        class Shader
        {
        public:

            enum ShaderType { VERTEX = GL_VERTEX_SHADER,
                              FRAGMENT = GL_FRAGMENT_SHADER,
                              COMPUTE = GL_COMPUTE_SHADER };

            Shader();
            Shader(const std::string &compute);
            Shader(const std::string &vertex, const std::string &frag);

            ~Shader();

            GLuint  getProgram();
            void    useProgram();

            void    setUniformValue(const glm::mat4 &matrix, const std::string &name);
            void    setUniformValue(const glm::vec3 &vec, const std::string &name);
            void    setUniformValue(const int value, const std::string &name);
            void    setUniformValue(const float value, const std::string &name);

            void    setAttribute(Buffer &buffer, GLuint attr, GLuint n_component);

            void    addShader(const std::string &file, const ShaderType &type);

            void    link();
        private:
            std::map<GLenum, GLuint>    _attached_shader;
            GLuint      _programID;

            GLuint      compile(const std::string &source, GLenum type);

        };
    }
}
#endif
