/**
 * @Author: danielb
 * @Date:   2017-07-22T23:35:22+02:00
 * @Last modified by:   danielb
 * @Last modified time: 2017-07-24T02:58:40+02:00
 */

#include "Window.hpp"
#include "Renderer.hpp"
#include "Object.hpp"
#include "Triangle.hpp"

using namespace mxe::scene::object;

int main()
{
    Window              window;
    mxe::Renderer       renderer(window);
    ObjectList          objects;
    float speed = 4.f; // 3 units / second
    float mouseSpeed = 0.05f;
    double oldx = 0, oldy = 0;

    Triangle triangle(glm::vec3(-1, 1, 0), glm::vec3(1, 1, 0), glm::vec3(0, 0, 0));

    objects.push_back(&triangle);

    while (1)
    {
        renderer.render(objects);

        SDL_Event event;
        while (window.pollEvent(event))
        {
            if (event.type == SDL_KEYDOWN)
            {
                if (event.key.keysym.sym == SDLK_LEFT)
                    renderer.camPos[0] -= 5. * (1.0 / renderer.fps);
                if (event.key.keysym.sym == SDLK_RIGHT)
                    renderer.camPos[0] += 5. * (1.0 / renderer.fps);
                if (event.key.keysym.sym == SDLK_UP)
                    renderer.camPos[1] += 5. * (1.0 / renderer.fps);
                if (event.key.keysym.sym == SDLK_DOWN)
                    renderer.camPos[1] -= 5. * (1.0 / renderer.fps);
                if (event.key.keysym.sym == SDLK_PAGEDOWN)
                    triangle.position[1] += 1. * (1.0 / renderer.fps);
                if (event.key.keysym.sym == SDLK_PAGEUP)
                    triangle.position[1] -= 1. * (1.0 / renderer.fps);
                if (event.key.keysym.sym == SDLK_ESCAPE)
                    {
                        window.close();
                        return (0);
                    }
            }

            if (event.type == SDL_MOUSEMOTION)
            {
                int xpos = 0, ypos = 0;

                // SDL_GetMouseState(&xpos, &ypos);
                // xpos = _width / 2.0 - xpos;
                // ypos = _width / 2.0 - ypos;
                // ypos = ypos - oldy;
                ypos = 0;

                xpos = event.motion.xrel;
                if (oldx != 0)
                    xpos = oldx - event.motion.xrel;

                std::cout << "xpos = " << xpos << " read pos: " << event.motion.x << " increase angle by " <<
                mouseSpeed * (1. / renderer.fps) * xpos << std::endl;

                renderer.horizontalAngle += mouseSpeed * (1. / renderer.fps) * xpos;
                renderer.verticalAngle   += mouseSpeed * (1. / renderer.fps) * ypos;

                std::cout << "angle:" << renderer.horizontalAngle << std::endl;

                oldx = oldx + xpos;
            }
        } // end event polling
    }

    return (0);
}
