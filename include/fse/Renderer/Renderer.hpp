/**
 * @Author: danielb
 * @Date:   2017-07-24T02:18:04+02:00
 * @Last modified by:   
 * @Last modified time: 2018-02-12T03:55:07+01:00
 */



#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <list>

#include "fse/Export.hpp"
#include "fse/Window.hpp"
#include "fse/Scene/Object/Object.hpp"
#include "fse/Scene/SceneManager.hpp"
#include "fse/Utils/FrameCounter.hpp"
#include "fse/ShaderManager.hpp"
#include "fse/Renderer/ObjectRenderer.hpp"
#include "fse/GLItem/Texture.hpp"

namespace fse {

    class FSE_API_EXPORT Renderer
    {
    public:
        explicit Renderer(Window &window);

        void    render(scene::SceneManager &scene, std::shared_ptr<fse::gl_item::Shader> shader = 0, bool clear_buffer = true, bool flip_buffer = true);

        const utils::FrameCounter     &getFrameCounter();

        glm::mat4 projection;
    private:
        Window                                  &_window;
        gl_item::Shader::AttributeHolder		_attribute;
        std::shared_ptr<gl_item::Texture>       _texture;

        renderer::ObjectRenderer                _object_renderer;

        // Initial Field of View
        float initialFoV = 45.0f;

        utils::FrameCounter     _fps;
        size_t  frame = 0;

    };

}

#endif
