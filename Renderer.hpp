/**
 * @Author: danielb
 * @Date:   2017-07-24T02:18:04+02:00
 * @Last modified by:   daniel_b
 * @Last modified time: 2017-08-16T16:47:13+02:00
 */



#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <list>

#include "Window.hpp"
#include "Object.hpp"
#include "Scene/SceneManager.hpp"
#include "Utils/FrameCounter.hpp"

namespace mxe {

    class Renderer
    {
    public:
        Renderer(Window &window);

        void    render(scene::SceneManager &scene);

    // private:
        Window      &_window;
        Shader      _shader;

        // Initial Field of View
        float initialFoV = 45.0f;

        utils::FrameCounter     fps;
        size_t  frame = 0;

        glm::mat4 projection;
    };

}

#endif
