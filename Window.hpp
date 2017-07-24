/**
 * @Author: danielb
 * @Date:   2017-07-22T23:17:54+02:00
 * @Last modified by:   danielb
 * @Last modified time: 2017-07-24T02:59:58+02:00
 */

#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <unistd.h>
#include <exception>
#include <string>

#include "Shader.hpp"
#include "Triangle.hpp"

class Window
{
public:
    Window(size_t width = 1280, size_t height = 720, const std::string &title = "My Window");

    void loop();

    void                flipScreen();

    bool                pollEvent(SDL_Event &event);

    const size_t        &getWidth();
    const size_t        &getHeight();

    void                setTitle(const std::string &title);

    void                close();

private:
    SDL_Window         *_window;
    SDL_GLContext       _context;
    size_t              _width;
    size_t              _height;
};

#endif
