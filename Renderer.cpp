/**
 * @Author: danielb
 * @Date:   2017-07-24T02:31:09+02:00
 * @Last modified by:   daniel_b
 * @Last modified time: 2017-08-30T05:03:03+02:00
 */



#include "Renderer.hpp"

using namespace mxe;

Renderer::Renderer(Window &window) :
    _window(window), _object_renderer(projection)
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

    _shader_manager.useDefaultProgram();

    for (auto obj : scene.getObjects())
    {
        glm::quat   quat(obj->getRotation());
        auto transform = glm::translate(obj->getPosition()) * glm::toMat4(quat);

        _object_renderer.addObject(obj->getMaterial(), obj->getMesh(), transform);
    }

    _shader_manager.getActualShader()->setUniformValue(projection, "projection");
    _shader_manager.getActualShader()->setUniformValue(view, "view");

    glm::vec3 tmp2(0, 04, 10);
    _shader_manager.getActualShader()->setUniformValue(tmp2, "light_pos");

    _shader_manager.getActualShader()->setUniformValue(scene.camera->getPosition(), "camera_position");

    _object_renderer.drawAll(_shader_manager);
    _object_renderer.clean();

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
