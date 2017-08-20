/**
 * @Author: danielb
 * @Date:   2017-07-24T02:31:09+02:00
 * @Last modified by:   daniel_b
 * @Last modified time: 2017-08-21T00:53:42+02:00
 */



#include "Renderer.hpp"

using namespace mxe;

Renderer::Renderer(Window &window) :
    _window(window), _shader("shader/basic.vert", "shader/basic.fragment")
{
    projection = glm::perspective<float>(45, // fov
                    (float) window.getWidth() / (float) window.getHeight(), // ratio
                    1.0, 100.0); // near / far

    GLuint VertexArrayID;
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);

    glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

    // Enable depth test
    glEnable(GL_DEPTH_TEST);
    // Accept fragment if it closer to the camera than the former one
    glDepthFunc(GL_LESS);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
}

void        Renderer::render(scene::SceneManager &scene)
{
    const glm::mat4 &view = scene.camera->getView();
    // glm::mat4 modelView = projection * view;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // glUseProgram(_shader.getProgram());

    scene.getDrawable()[0]->getMaterial()->getShader().setUniformValue(projection, "projection");
    scene.getDrawable()[0]->getMaterial()->getShader().setUniformValue(view, "view");

    glm::vec3 tmp2(0, 04, 10);
    scene.getDrawable()[0]->getMaterial()->getShader().setUniformValue(tmp2, "light_pos");

    scene.getDrawable()[0]->getMaterial()->getShader().setUniformValue(scene.camera->getPosition(), "camera_position");

    for (auto obj : scene.getDrawable())
    {
        obj->draw(projection, view, glm::mat4(1.0), scene.camera->getPosition());
    }

    _window.flipScreen();

    fps.update();
    if (frame > 10)
    {
        frame = 0;
        std::string title = "FPS: " + std::to_string(fps.getFrameRate());
        _window.setTitle(title);
    }
    frame++;
}
