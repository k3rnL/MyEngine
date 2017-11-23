/**
* @Author: danielb
* @Date:   2017-07-22T23:22:41+02:00
 * @Last modified by:   daniel_b
 * @Last modified time: 2017-11-15T20:02:21+01:00
*/

#include "fse/Window.hpp"

Window::Window(size_t width, size_t height, const std::string &title)
{
    SDL_Init(SDL_INIT_VIDEO);

    _window = SDL_CreateWindow("Test SDL 2.0", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
    std::cerr << "Surface:" << _window << std::endl;

    SDL_SetRelativeMouseMode(SDL_TRUE);


    GLenum err;
    while((err = glGetError()) != GL_NO_ERROR)
    {
      std::cout << "[ERROR] gl err = " << err << "\n";
    }
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    _context = SDL_GL_CreateContext(_window);
    glewExperimental = GL_TRUE;
    if ((err = glewInit()) != GLEW_OK)
    {
        std::cerr << "Cannot initialize GLEW\n" <<
                    glewGetErrorString(err) << std::endl;
        // throw std::exception();
    }
    _width = width;
    _height = height;
}

bool            Window::pollEvent(SDL_Event &event)
{
    return (SDL_PollEvent(&event));
}

void            Window::flipScreen()
{
    SDL_GL_SwapWindow(_window);
}

const size_t    &Window::getWidth() {
    return (_width);
}

const size_t    &Window::getHeight() {
    return (_height);
}

void            Window::setTitle(const std::string &title)
{
    SDL_SetWindowTitle(_window, title.c_str());
}

void            Window::close()
{
    SDL_GL_DeleteContext(_context);
    SDL_DestroyWindow(_window);
    SDL_Quit();
}

void Window::loop()
{

}
