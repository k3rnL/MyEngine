/**
 * @Author: danielb
 * @Date:   2017-07-24T02:31:09+02:00
 * @Last modified by:   daniel_b
 * @Last modified time: 2017-08-10T00:44:33+02:00
 */



#include "Renderer.hpp"

using namespace mxe;

Renderer::Renderer(Window &window) :
    _window(window), _shader("shader/basic.vert", "shader/basic.fragment")
{
    projection = glm::perspective<float>(45, // fov
                    (float) window.getWidth() / (float) window.getHeight(), // ratio
                    1.0, 100.0); // near / far
    view = glm::lookAt(glm::vec3(4, 4, 3),
                       glm::vec3(0, 0, 0),
                       glm::vec3(0, 1, 0));
    camPos = glm::vec3(0, 0, 3);

    GLuint VertexArrayID;
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);

    glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

    // Enable depth test
    glEnable(GL_DEPTH_TEST);
    // Accept fragment if it closer to the camera than the former one
    glDepthFunc(GL_LESS);
}

void        Renderer::render(scene::object::ObjectList &objs)
{
    glm::mat4 modelView(1.0);
    // modelView = glm::translate(glm::vec3(0, 4, 0));
    glm::vec3 direction(
      cos(verticalAngle) * sin(horizontalAngle),
      sin(verticalAngle),
      cos(verticalAngle) * cos(horizontalAngle));
    glm::vec3 right = glm::vec3(
      sin(horizontalAngle - 3.14f/2.0f),
      0,
      cos(horizontalAngle - 3.14f/2.0f));
      glm::vec3 up = glm::cross( right, direction );
    view = glm::lookAt(camPos, camPos + direction, up);

    // modelView =  view * modelView;
    modelView = projection * view * modelView;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // glUseProgram(_shader.getProgram());

    for (auto obj : objs)
    {
        obj->draw(projection, view, camPos);
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
