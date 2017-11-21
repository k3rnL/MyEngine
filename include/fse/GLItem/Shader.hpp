/**
 * @Author: danielb
 * @Date:   2017-07-23T01:38:03+02:00
 * @Last modified by:   daniel_b
 * @Last modified time: 2017-11-16T05:48:53+01:00
 */

#ifndef SHADER_HPP
#define SHADER_HPP

#include <string>
#include <fstream>
#include <iostream>
#include <vector>

#include <GL/glew.h>
#include <glm/glm.hpp>

#include <fse/GLItem/Buffer.hpp>

namespace fse {
    namespace gl_item {

        class Shader
        {
        public:
            Shader(const std::string &vertex, const std::string &frag);

            GLuint  getProgram();
            void    useProgram();

            void    setUniformValue(const glm::mat4 &matrix, const std::string &name);
            void    setUniformValue(const glm::vec3 &vec, const std::string &name);
            void    setUniformValue(const int value, const std::string &name);
            void    setUniformValue(const float value, const std::string &name);

            void    setAttribute(Buffer &buffer, GLuint attr, GLuint n_component);

        private:

            GLuint      compile(const std::string &source, GLenum type);

            GLuint      _vertexID;
            GLuint      _fragmentID;
            GLuint      _programID;
        };
    }
}
#endif
