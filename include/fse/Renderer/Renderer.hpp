/**
 * @Author: danielb
 * @Date:   2017-07-24T02:18:04+02:00
 * @Last modified by:   daniel_b
 * @Last modified time: 2017-11-20T23:58:04+01:00
 */



#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <list>

#include "fse/Window.hpp"
#include "fse/Scene/Object/Object.hpp"
#include "fse/Scene/SceneManager.hpp"
#include "fse/Utils/FrameCounter.hpp"
#include "fse/ShaderManager.hpp"
#include "fse/Renderer/ObjectRenderer.hpp"

namespace fse {

    class Renderer
    {
    public:
        Renderer(Window &window);

        void    render(scene::SceneManager &scene);

        const utils::FrameCounter     &getFrameCounter();

        glm::mat4 projection;
    private:
        Window          &_window;

        renderer::ObjectRenderer    _object_renderer;

        // Initial Field of View
        float initialFoV = 45.0f;

        utils::FrameCounter     _fps;
        size_t  frame = 0;

    };

}

#endif
