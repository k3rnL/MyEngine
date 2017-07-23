/**
 * @Author: danielb
 * @Date:   2017-07-22T23:22:41+02:00
 * @Last modified by:   danielb
 * @Last modified time: 2017-07-23T04:21:53+02:00
 */

#include "Window.hpp"

Window::Window(size_t width, size_t height, const std::string &title)
{
    if (!glfwInit())
        throw std::exception();
    glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // On veut OpenGL 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // Pour rendre MacOS heureux ; ne devrait pas être nécessaire
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // On ne veut pas l'ancien OpenGL
    _window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
    if (!_window)
        throw std::exception();
    glfwMakeContextCurrent(_window);
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)
        throw std::exception();
    _width = width;
    _height = height;

}

void Window::loop()
{
    // init triangle
    GLfloat g_vertex_buffer_data[] = {
        -1.0f, -1.0f, 0.0f,
        1.0f, -1.0f, 0.0f,
        0.0f,  1.0f, 0.0f,
    };


    glfwPollEvents();

    GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

    Shader shader("shader/basic.vert", "shader/basic.fragment");

    GLuint vertexbuffer;
	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
    // end init

    glm::mat4 projection = glm::perspective<float>(45, (float) _width / (float) _height, 1.0, 100.0);
    glm::mat4 view = glm::lookAt(glm::vec3(4, 4, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
    glm::vec3 camPos(4, 4, 3);

    glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
    while (glfwGetKey(_window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
            glfwWindowShouldClose(_window) == 0)
            {
                glm::mat4 modelView(1.0);
                view = glm::lookAt(camPos, glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
                modelView = projection * view * modelView;

                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
                glUseProgram(shader.getProgram());
                //draw
                glEnableVertexAttribArray(0);
                glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
                glVertexAttribPointer(
                    0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
                    3,                  // size
                    GL_FLOAT,           // type
                    GL_FALSE,           // normalized?
                    0,                  // stride
                    (void*)0            // array buffer offset
                    );

                GLuint MatrixID = glGetUniformLocation(shader.getProgram(), "MVP");
                glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &modelView[0][0]);

                // Draw the triangle !
                glDrawArrays(GL_TRIANGLES, 0, 3); // 3 indices starting at 0 -> 1 triangle

		              glDisableVertexAttribArray(0);
                      //end

                glfwSwapBuffers(_window);
                glfwPollEvents();

                if (glfwGetKey(_window, GLFW_KEY_LEFT) == GLFW_PRESS)
                    camPos[0] -= 0.01;
                if (glfwGetKey(_window, GLFW_KEY_RIGHT) == GLFW_PRESS)
                    camPos[0] += 0.01;
            }
}
