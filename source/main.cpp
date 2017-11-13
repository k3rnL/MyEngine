/**
 * @Author: danielb
 * @Date:   2017-07-22T23:35:22+02:00
 * @Last modified by:   daniel_b
 * @Last modified time: 2017-11-13T00:47:53+01:00
 */

#include "fse/Window.hpp"
#include "fse/Renderer.hpp"
#include "fse/Object.hpp"
#include "fse/Triangle.hpp"
#include "fse/Scene/Object/Wavefront.hpp"
#include "fse/Scene/SceneManager.hpp"
#include "fse/Scene/CameraFPS.hpp"

using namespace fse::scene::object;

int main()
{
    Window                      window;
    fse::Renderer               renderer(window);
    fse::scene::SceneManager    scene;
    fse::scene::CameraFPS       camera;
    ObjectList                  objects;
    float speed = 4.f; // 3 units / second

    scene.camera = &camera;

    Wavefront wavefront("Ressource/cube.obj");
    // wavefront.getMaterial().setTexture("Ressource/alduin.bmp");


    Wavefront wavefront2("Ressource/teapot.obj");
    // Triangle triangle(glm::vec3(-1, 1, 0), glm::vec3(1, 1, 0), glm::vec3(0, 0, 0));
    // Wavefront wavefront("/home/daniel_b/gfx_raytracer2/Wavefront/cow.obj");

    for (int i = 0 ; i < 000 ; i++)
    {
      Wavefront *w = scene.addWavefront("Ressource/alduin.obj");
      w->getPosition()[0] = rand() % 100 - 50;
      w->getPosition()[1] = rand() % 100;
      w->getPosition()[2] = rand() % 100 - 50;
      // w->getMaterial().setTexture("Ressource/alduin.bmp");
      objects.push_back(w);
    }

    wavefront.getPosition().y += 1;
    wavefront.getPosition().y += 90;

    // objects.push_back(&triangle);
    objects.push_back(&wavefront);
    objects.push_back(&wavefront2);

    while (1)
    {
        renderer.render(scene);

        float   move_handle = 1. / renderer.fps.getFrameRate();

        wavefront.getRotation().y += 1 * move_handle;

        SDL_Event event;
        while (window.pollEvent(event))
        {
            if (event.type == SDL_KEYDOWN)
            {
              glm::vec3 direction = camera.getDirection();

                if (event.key.keysym.sym == SDLK_z)
                    camera.getPosition() += glm::vec3(speed) * direction * glm::vec3(move_handle);
                if (event.key.keysym.sym == SDLK_s)
                  camera.getPosition() -= glm::vec3(speed) * direction * glm::vec3(move_handle);
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
                camera.mouseInput(xpos, ypos, move_handle);
            }
        } // end event polling
    }


    return (0);
}
