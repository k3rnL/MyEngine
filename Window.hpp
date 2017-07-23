/**
 * @Author: danielb
 * @Date:   2017-07-22T23:17:54+02:00
 * @Last modified by:   danielb
 * @Last modified time: 2017-07-23T05:14:50+02:00
 */

#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <exception>
#include <string>

#include "Shader.hpp"
#include "Triangle.hpp"

class Window
{
public:
    Window(size_t width = 1280, size_t height = 720, const std::string &title = "My Window");

    void loop();
private:
    GLFWwindow          *_window;
    size_t              _width;
    size_t              _height;
};

#endif
