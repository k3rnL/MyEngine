/**
 * @Author: daniel_b
 * @Date:   2017-12-16T01:33:06+01:00
 * @Last modified by:   daniel_b
 * @Last modified time: 2017-12-16T02:04:56+01:00
 */


#ifndef FSE_TEXTURE_RENDERER_HPP
#define FSE_TEXTURE_RENDERER_HPP

#include <GL/glew.h>
#include <glm/glm.hpp>

#include "fse/Window.hpp"
#include "fse/GLItem/Texture.hpp"
#include "fse/GLItem/Mesh.hpp"

namespace fse {
    namespace renderer {

        class TextureRenderer
        {
        public:
            TextureRenderer(Window &win);

            void                                setTexture(std::shared_ptr<gl_item::Texture> texture);
            std::shared_ptr<gl_item::Texture>   getTexture();

            void                                draw();

        private:
            Window                              &_window;

            std::shared_ptr<gl_item::Texture>   _texture;
            std::shared_ptr<gl_item::Shader>    _shader;
            gl_item::Mesh                       mesh;
        };

    }
}

#endif /* end of include guard: FSE_TEXTURE_RENDERER_HPP */
