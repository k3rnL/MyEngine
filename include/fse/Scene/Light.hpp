/**
 * @Author: daniel_b
 * @Date:   2017-11-13T02:45:30+01:00
 * @Last modified by:   daniel_b
 * @Last modified time: 2017-11-13T03:41:04+01:00
 */


#ifndef FSE_LIGHT_HPP
#define FSE_LIGHT_HPP

#include <GL/glew.h>
#include <glm/glm.hpp>

#include "fse/Scene/INode.hpp"
#include "fse/GLItem/Texture.hpp"
#include "fse/Renderer/ObjectRenderer.hpp"

namespace fse {
    namespace scene {

        class Light : public INode
        {
        public:
             Light();

             void   updateShadowMap(fse::renderer::ObjectRenderer &obj_renderer);

             glm::mat4                          getMVP();
             std::shared_ptr<gl_item::Texture>  getTexture();
         private:
             GLuint                             _frame_buffer;
             std::shared_ptr<gl_item::Texture>  _texture;
        };

    }
}

#endif /* end of include guard: FSE_LIGHT_HPP */
