/**
 * @Author: danielb
 * @Date:   2017-07-23T01:38:03+02:00
 * @Last modified by:
 * @Last modified time: 2018-02-14T02:15:56+01:00
 */

#ifndef SHADER_HPP
#define SHADER_HPP

#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <map>
#include <memory>

#include <GL/glew.h>
#include <glm/glm.hpp>

#include "fse/Export.hpp"
#include <fse/GLItem/Buffer.hpp>

namespace fse {
    namespace gl_item {

        class FSE_API_EXPORT Shader
        {
        public:

            enum ShaderType { VERTEX = GL_VERTEX_SHADER,
                              FRAGMENT = GL_FRAGMENT_SHADER,
                              COMPUTE = GL_COMPUTE_SHADER };

            Shader();
            Shader(const std::string &vertex, const std::string &frag);

            explicit Shader(const std::string &compute);

            ~Shader();

            GLuint  getProgram();
            void    useProgram();

            void    setUniformValue(const glm::mat4 &matrix, const std::string &name);
            void    setUniformValue(const glm::vec3 &vec, const std::string &name);
            void    setUniformValue(const int value, const std::string &name);
            void    setUniformValue(const float value, const std::string &name);

			template <typename T>
            void    setAttribute(Buffer<T> &buffer, GLuint attr, GLuint n_component) {
				glEnableVertexAttribArray(attr);
				buffer.bind();
				glVertexAttribPointer(
					attr,               // attribute must match the layout in the shader.
					n_component,      // size
					GL_FLOAT,           // type
					GL_FALSE,           // normalized?
					0,                  // stride
					(void*)0            // array buffer offset
				);
			}

            void    addShader(const std::string &file, const ShaderType &type);

            void    updateShader();

            void    link();

            class Attribute
            {
            public:
                virtual void    apply(std::shared_ptr<Shader> shader) = 0;
            };

			template <class T>
			class Uniform : public Attribute
			{
			public:
				Uniform(const std::string &name, const T &value) : name(name) {

				}

				const T     &getValue() const { return value; }
				T           getValue() { return value; }

				void        setValue(const T value) { this->value = value; }

				const std::string       &getName() { return name; }

				virtual void    apply(std::shared_ptr<Shader> shader) {
					shader->setUniformValue(value, name);
				}

			private:
				T                       value;
				const std::string       name;
			};

            class AttributeHolder
            {
            public:
                template <class T>
                void    addUniform(const std::string &name, const T &value) {
                    if (uniforms[name] == 0)
                        uniforms[name] = new Uniform<T>(name, value);
                    ((Uniform<T> *) uniforms[name])->setValue(value);
                }

                void    deleteUniform(const std::string &name) {
                    delete uniforms[name];
                    uniforms[name] = 0;
                }

                void    apply(std::shared_ptr<Shader> shader) {
                    for (auto uniform : uniforms) {
                        uniform.second->apply(shader);
                    }
                }

            private:
                std::map<std::string, Attribute *>      uniforms;
            };

        private:
            std::map<GLenum, std::tuple<GLuint, std::string> > _attached_shader;
            GLuint      _programID;

            GLuint      compile(const std::string &source, GLenum type);

        };
    }
}
#endif
