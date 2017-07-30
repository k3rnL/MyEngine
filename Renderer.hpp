/**
 * @Author: danielb
 * @Date:   2017-07-24T02:18:04+02:00
 * @Last modified by:   daniel_b
 * @Last modified time: 2017-07-30T23:29:37+02:00
 */



#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <list>

#include "Window.hpp"
#include "Object.hpp"
#include "Utils/FrameCounter.hpp"

namespace mxe {

    class Renderer
    {
    public:
        Renderer(Window &window);

        void    render(scene::object::ObjectList &objs);

    // private:
        Window      &_window;
        Shader      _shader;

        float horizontalAngle = 3.14f;
        // vertical angle : 0, look at the horizon
        float verticalAngle = 0.0f;
        // Initial Field of View
        float initialFoV = 45.0f;

        utils::FrameCounter     fps;
        size_t  frame = 0;

        glm::mat4 projection;
        glm::mat4 view;
        glm::vec3 camPos;
    };

}

#endif
