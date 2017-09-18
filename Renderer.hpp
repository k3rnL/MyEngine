/**
 * @Author: danielb
 * @Date:   2017-07-24T02:18:04+02:00
 * @Last modified by:   daniel_b
 * @Last modified time: 2017-09-18T14:28:50+02:00
 */



#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <list>

#include "Window.hpp"
#include "Object.hpp"
#include "Scene/SceneManager.hpp"
#include "Utils/FrameCounter.hpp"
#include "Mxe/ShaderManager.hpp"
#include "Mxe/Renderer/ObjectRenderer.hpp"

namespace mxe {

    class Renderer
    {
    public:
        Renderer(Window &window);

        void    render(scene::SceneManager &scene);

        const utils::FrameCounter     &getFrameCounter();

    private:
        Window          &_window;

        renderer::ObjectRenderer    _object_renderer;

        // Initial Field of View
        float initialFoV = 45.0f;

        utils::FrameCounter     _fps;
        size_t  frame = 0;

        glm::mat4 projection;
    };

}

#endif
