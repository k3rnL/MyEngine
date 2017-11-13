/**
 * @Author: daniel_b
 * @Date:   2017-11-13T01:18:27+01:00
 * @Last modified by:   daniel_b
 * @Last modified time: 2017-11-13T02:20:42+01:00
 */

#ifndef FSE_TEXTURE_HPP
#define FSE_TEXTURE_HPP

#include <string>
#include <memory>

#include <GL/glew.h>
#include <glm/glm.hpp>

namespace fse {
    namespace gl_item {

        class Texture
        {
        public:
            enum Format { RED = GL_RED,
                          RG = GL_RG,
                          RGB = GL_RGB,
                          BGR = GL_BGR, RGBA = GL_RGBA,
                          BGRA = GL_BGRA,
                          DETPH = GL_DEPTH
                        };

            enum InternalFormat { DEPTH = GL_DEPTH_COMPONENT,
                                  DEPTH16 = GL_DEPTH_COMPONENT16,
                                  DEPTH24 = GL_DEPTH_COMPONENT24,
                                  DEPTH32 = GL_DEPTH_COMPONENT32,
                                  RGB8 = GL_RGB8,
                                  RGB10 = GL_RGB10
                                };

            enum Type { UNSIGNED_BYTE,
                        BYTE,
                        FLOAT
                      };

            static std::shared_ptr<Texture> create(size_t x, size_t y, InternalFormat format, Type type);
            static std::shared_ptr<Texture> load(std::string const &file);

            Texture();
            ~Texture();

            void    setMipMapLevel();
            void    bind();
            void    activate(int slot);
            GLuint  getId();
            void    loadImage(std::string const &name);

        private:
            GLuint      _id;
            glm::vec2   _size;
        };

    }
}

#endif /* end of include guard: FSE_TEXTURE_HPP */
