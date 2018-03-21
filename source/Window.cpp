/**
* @Author: danielb
* @Date:   2017-07-22T23:22:41+02:00
 * @Last modified by:
 * @Last modified time: 2018-02-05T03:08:06+01:00
*/

#include "fse/Window.hpp"

std::map<Uint32, std::list<SDL_Event>>	Window::event_stack;

Window::Window(size_t width, size_t height, const std::string &title)
{
    SDL_Init(SDL_INIT_VIDEO);

    _window = SDL_CreateWindow("Test SDL 2.0", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, (int) width, (int) height, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
    std::cerr << "Surface:" << _window << std::endl;

    SDL_SetRelativeMouseMode(SDL_TRUE);
    GLenum err;/*
    while((err = glGetError()) != GL_NO_ERROR)
    {
      std::cout << "[ERROR] gl err = " << err << "\n";
    }*/
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

void			Window::captureMouse(bool c) {
	SDL_SetRelativeMouseMode(c ? SDL_TRUE : SDL_FALSE);
}

void			Window::makeContextCurrent() {
	SDL_GL_MakeCurrent(_window, _context);
}

void			Window::setOnMouseClick(std::function<void(int, int)> fct) {
	onClick = fct;
}

void			Window::setOnMouseClickReleased(std::function<void(int, int)> fct) {
	onClickReleased = fct;
}

void			Window::setResizable(bool r) {
	SDL_SetWindowResizable(_window, r ? SDL_TRUE : SDL_FALSE);
}

bool			Window::isOpen() {
	return _window ? true : false;
}

bool            Window::pollEvent(SDL_Event &event)
{
	if (event_stack[SDL_GetWindowID(_window)].size() > 0) {
		event = event_stack[SDL_GetWindowID(_window)].front();
		event_stack[SDL_GetWindowID(_window)].pop_front();
	}
	else if (!SDL_PollEvent(&event))
		return false;
	if (event.window.windowID != SDL_GetWindowID(_window)) {
		event_stack[event.window.windowID].push_back(event);
		return (pollEvent(event));
	}
	if (event.type == SDL_MOUSEBUTTONDOWN) {
		if (event.button.button == SDL_BUTTON_LEFT)
			if (onClick)
				onClick(event.motion.x, event.motion.y);
	}
	if (event.type == SDL_MOUSEBUTTONUP) {
		if (event.button.button == SDL_BUTTON_LEFT)
			if (onClickReleased)
				onClickReleased(event.motion.x, event.motion.y);
	}
	return (true);
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
	_window = 0;
}

void Window::loop()
{

}
