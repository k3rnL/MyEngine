/**
 * @Author: danielb
 * @Date:   2017-07-24T02:18:04+02:00
 * @Last modified by:   danielb
 * @Last modified time: 2017-07-24T02:56:41+02:00
 */



#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <list>

#include "Window.hpp"
#include "Object.hpp"

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

        clock_t current_tick, delta_tick;
        clock_t fps;
        size_t  frame = 0;

        glm::mat4 projection;
        glm::mat4 view;
        glm::vec3 camPos;
    };

}

#endif
