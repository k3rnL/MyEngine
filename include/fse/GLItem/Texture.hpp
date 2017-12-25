
/**
 * @Author: daniel_b
 * @Date:   2017-11-13T01:18:27+01:00
 * @Last modified by:   daniel_b
 * @Last modified time: 2017-12-14T22:30:18+01:00
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
                          RGBA = GL_RGBA,
                          BGR = GL_BGR,
                          BGRA = GL_BGRA,
                          DETPH_COMPONENT = GL_DEPTH_COMPONENT
                        };

            enum InternalFormat { DEPTH = GL_DEPTH_COMPONENT,
                                  DEPTH16 = GL_DEPTH_COMPONENT16,
                                  DEPTH24 = GL_DEPTH_COMPONENT24,
                                  DEPTH32 = GL_DEPTH_COMPONENT32,
                                  RGB8 = GL_RGB8,
                                  RGB10 = GL_RGB10,
                                  RGBA32F = GL_RGBA32F
                                };

            enum Type { UNSIGNED_BYTE = GL_UNSIGNED_BYTE,
                        BYTE = GL_BYTE,
                        FLOAT = GL_FLOAT
                      };

            static std::shared_ptr<Texture> create(size_t x, size_t y, InternalFormat in_format, Format format, Type type);
            static std::shared_ptr<Texture> load(std::string const &file);

            Texture();
            ~Texture();

            void    setMipMapLevel(int level);
            void    bind();
            void    unbind();
            void    activate(int slot);
            GLuint  getId();
            void    loadImage(std::string const &name);

            glm::vec2   _size;
        private:
            GLuint      _id;
        };

    }
}

#endif /* end of include guard: FSE_TEXTURE_HPP */
