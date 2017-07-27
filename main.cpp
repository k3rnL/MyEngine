/**
 * @Author: danielb
 * @Date:   2017-07-22T23:35:22+02:00
 * @Last modified by:   daniel_b
 * @Last modified time: 2017-07-27T01:53:38+02:00
 */

#include "Window.hpp"
#include "Renderer.hpp"
#include "Object.hpp"
#include "Triangle.hpp"
#include "Scene/Object/Wavefront.hpp"

using namespace mxe::scene::object;

int main()
{
    Window              window;
    mxe::Renderer       renderer(window);
    ObjectList          objects;
    float speed = 4.f; // 3 units / second
    float mouseSpeed = 0.05f;
    double oldx = 0, oldy = 0;

    Wavefront wavefront("Ressource/teapot.obj");
    Triangle triangle(glm::vec3(-1, 1, 0), glm::vec3(1, 1, 0), glm::vec3(0, 0, 0));
    // Wavefront wavefront("/home/daniel_b/gfx_raytracer2/Wavefront/cow.obj");

    wavefront.position.y += 1;

    objects.push_back(&triangle);
    objects.push_back(&wavefront);

    while (1)
    {
        renderer.render(objects);

        SDL_Event event;
        // while (window.pollEvent(event))
        window.pollEvent(event);
        {
            if (event.type == SDL_KEYDOWN)
            {
                if (event.key.keysym.sym == SDLK_LEFT)
                    renderer.camPos[0] -= 25. * (1.0 / renderer.fps);
                if (event.key.keysym.sym == SDLK_RIGHT)
                    renderer.camPos[0] += 25. * (1.0 / renderer.fps);
                if (event.key.keysym.sym == SDLK_UP)
                    renderer.camPos[1] += 25. * (1.0 / renderer.fps);
                if (event.key.keysym.sym == SDLK_DOWN)
                    renderer.camPos[1] -= 25. * (1.0 / renderer.fps);
                if (event.key.keysym.sym == SDLK_PAGEDOWN)
                    wavefront.position[1] += 11. * (1.0 / renderer.fps);
                if (event.key.keysym.sym == SDLK_PAGEUP)
                    wavefront.position[1] -= 11. * (1.0 / renderer.fps);
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
