/**
 * @Author: danielb
 * @Date:   2017-07-22T23:35:22+02:00
 * @Last modified by:   daniel_b
 * @Last modified time: 2017-07-31T04:36:47+02:00
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
    float mouseSpeed = 1;

    Wavefront wavefront("Ressource/alduin.obj");
    Wavefront wavefront2("Ressource/teapot.obj");
    Triangle triangle(glm::vec3(-1, 1, 0), glm::vec3(1, 1, 0), glm::vec3(0, 0, 0));
    // Wavefront wavefront("/home/daniel_b/gfx_raytracer2/Wavefront/cow.obj");

    for (int i = 0 ; i < 5 ; i++)
    {
      Wavefront *w = new Wavefront("Ressource/alduin.obj");
      w->position[0] = rand() % 100 - 50;
      w->position[1] = rand() % 100;
      w->position[2] = rand() % 100 - 50;
      objects.push_back(w);
    }

    wavefront.position.y += 1;
    wavefront.rotation.y += 90;

    objects.push_back(&triangle);
    objects.push_back(&wavefront);
    objects.push_back(&wavefront2);

    while (1)
    {
        renderer.render(objects);

        float   move_handle = 1. / renderer.fps.getFrameRate();

        wavefront.rotation.y += 1 * move_handle;

        SDL_Event event;
        while (window.pollEvent(event))
        {
            if (event.type == SDL_KEYDOWN)
            {
              glm::vec3 direction(
                cos(renderer.verticalAngle) * sin(renderer.horizontalAngle),
                sin(renderer.verticalAngle),
                cos(renderer.verticalAngle) * cos(renderer.horizontalAngle));

                direction = glm::normalize(direction);

                if (event.key.keysym.sym == SDLK_LEFT)
                    renderer.horizontalAngle += speed * (move_handle);
                if (event.key.keysym.sym == SDLK_RIGHT)
                    renderer.horizontalAngle -= speed * (move_handle);
                if (event.key.keysym.sym == SDLK_PAGEDOWN)
                  renderer.verticalAngle -= speed * (move_handle);
                if (event.key.keysym.sym == SDLK_PAGEUP)
                  renderer.verticalAngle += speed * (move_handle);
                if (event.key.keysym.sym == SDLK_UP)
                    renderer.camPos += glm::vec3(speed) * direction * glm::vec3(move_handle);
                if (event.key.keysym.sym == SDLK_DOWN)
                  renderer.camPos -= glm::vec3(speed) * direction * glm::vec3(move_handle);
                if (event.key.keysym.sym == SDLK_ESCAPE)
                    {
                        window.close();
                        return (0);
                    }
            }

            if (event.type == SDL_MOUSEMOTION)
            {
                int xpos = 0, ypos = 0;
                SDL_GetRelativeMouseState(&xpos, &ypos);

                renderer.horizontalAngle += mouseSpeed * (move_handle) * -xpos;
                renderer.verticalAngle   += mouseSpeed * (move_handle) * -ypos;
            }
        } // end event polling
    }

    return (0);
}
