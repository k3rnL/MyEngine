/**
 * @Author: danielb
 * @Date:   2017-07-24T02:31:09+02:00
 * @Last modified by:   daniel_b
 * @Last modified time: 2017-11-15T15:43:25+01:00
 */



#include "fse/Renderer/Renderer.hpp"

using namespace fse;

Renderer::Renderer(Window &window) :
    _window(window), _object_renderer()
{
    projection = glm::perspective<float>(45, // fov
                    (float) window.getWidth() / (float) window.getHeight(), // ratio
                    0.1, 100.0); // near / far

    projection = glm::perspective<float>(45, // fov
                    (float) 1024 / (float) 1024, // ratio
                    0.1, 100.0); // near / far

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

    ShaderManager::getInstance().addShader("basic_light");
}

void        Renderer::render(scene::SceneManager &scene)
{
    const glm::mat4 &view = scene.camera->getView();
    // glm::mat4 modelView = projection * view;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    _object_renderer.setShadowMap(scene.getLight()->getTexture());
    for (auto node : scene.getNodes()) {
        _object_renderer.addNode(node);
    }
    static float time_i = 0;

    scene.getLight()->updateShadowMap(_object_renderer);

    ShaderManager::getInstance().setUniformValue(time_i+=1.0/_fps.getFrameRate(), "time");

    ShaderManager::getInstance().setUniformValue(projection, "projection");
    ShaderManager::getInstance().setUniformValue(view, "view");

    ShaderManager::getInstance().setUniformValue(scene.getLight()->getPosition(), "light_pos");
    ShaderManager::getInstance().setUniformValue(scene.getLight()->getMVP(), "light_mvp");

    ShaderManager::getInstance().setUniformValue(scene.camera->getPosition(), "camera_position");

    glViewport(0, 0, _window.getWidth(), _window.getHeight());
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    _object_renderer.drawAll();
    _object_renderer.clean();

    _window.flipScreen();

    _fps.update();
    if (frame > 10)
    {
        frame = 0;
        std::string title = "FPS: " + std::to_string(_fps.getFrameRate());
        _window.setTitle(title);
    }
    frame++;
}


const utils::FrameCounter     &Renderer::getFrameCounter()
{
    return (_fps);
}
