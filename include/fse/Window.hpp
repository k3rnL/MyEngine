/**
 * @Author: danielb
 * @Date:   2017-07-22T23:17:54+02:00
 * @Last modified by:   daniel_b
 * @Last modified time: 2018-02-13T01:05:11+01:00
 */

#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <functional>
#include <exception>
#include <string>
#include <list>

#include <fse/Export.hpp>
#include <fse/GLItem/Shader.hpp>

class FSE_API_EXPORT Window
{
public:
    Window(size_t width = 1280, size_t height = 720, const std::string &title = "My Window");

    void loop();

    void                flipScreen();

    bool                pollEvent(SDL_Event &event);

    const size_t        &getWidth();
    const size_t        &getHeight();

    void                setTitle(const std::string &title);

	void				setResizable(bool resize);
	void				captureMouse(bool capture);
	void				setOnMouseClick(std::function<void(int x, int y)> callback);

    void                close();
	bool				isOpen();
	void				makeContextCurrent();

private:
	std::function<void(int, int)>	onClick;
	static std::map<Uint32, std::list<SDL_Event>>	event_stack;
    SDL_Window         *_window;
    SDL_GLContext       _context;
    size_t              _width;
    size_t              _height;
};

#endif
