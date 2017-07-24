/**
* @Author: danielb
* @Date:   2017-07-22T23:22:41+02:00
 * @Last modified by:   danielb
 * @Last modified time: 2017-07-24T01:08:20+02:00
*/

#include "Window.hpp"

Window::Window(size_t width, size_t height, const std::string &title)
{
    SDL_Init(SDL_INIT_VIDEO);

    _window = SDL_CreateWindow("Test SDL 2.0", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
    std::cerr << "Surface:" << _window << std::endl;

    SDL_SetRelativeMouseMode(SDL_TRUE);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    _context = SDL_GL_CreateContext(_window);
    glewExperimental = GL_TRUE;
    GLenum err;
    if ((err = glewInit()) != GLEW_OK)
    {
        std::cerr << "Cannot initialize GLEW\n" <<
                    glewGetErrorString(err) << std::endl;
        // throw std::exception();
    }
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
    glm::vec3 camPos(0, 0, 3);

    float horizontalAngle = 3.14f;
    // vertical angle : 0, look at the horizon
    float verticalAngle = 0.0f;
    // Initial Field of View
    float initialFoV = 45.0f;

    float speed = 4.f; // 3 units / second
    float mouseSpeed = 0.05f;
    double oldx = 0, oldy = 0;
    // glfwSetCursorPos(_window, 0, 0);


    clock_t current_tick, delta_tick;
    clock_t fps;
    size_t  frame = 0;

    Triangle triangle(glm::vec3(-1, 1, 0), glm::vec3(1, 1, 0), glm::vec3(0, 0, 0));

    glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
    while (1)
    {
        current_tick = clock();

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

        modelView = projection * view * modelView;

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glUseProgram(shader.getProgram());
        //draw

        triangle.draw(shader, modelView);

        //end

        SDL_GL_SwapWindow(_window);

        SDL_Event event;

        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_KEYDOWN)
            {
                if (event.key.keysym.sym == SDLK_LEFT)
                    camPos[0] -= 5. * (1.0 / fps);
                if (event.key.keysym.sym == SDLK_RIGHT)
                    camPos[0] += 5. * (1.0 / fps);
                if (event.key.keysym.sym == SDLK_UP)
                    camPos[1] += 5. * (1.0 / fps);
                if (event.key.keysym.sym == SDLK_DOWN)
                    camPos[1] -= 5. * (1.0 / fps);
                if (event.key.keysym.sym == SDLK_PAGEDOWN)
                    triangle.position[1] += 1. * (1.0 / fps);
                if (event.key.keysym.sym == SDLK_PAGEUP)
                    triangle.position[1] -= 1. * (1.0 / fps);
                if (event.key.keysym.sym == SDLK_ESCAPE)
                    {
                        SDL_GL_DeleteContext(_context);
                        SDL_DestroyWindow(_window);
                        SDL_Quit();
                        return ;
                    }
            }

            if (event.type == SDL_MOUSEMOTION)
            {
                int xpos = 0, ypos = 0;

                // SDL_GetMouseState(&xpos, &ypos);
                // xpos = _width / 2.0 - xpos;
                // ypos = _width / 2.0 - ypos;
                // ypos = ypos - oldy;
                ypos = 0;

                xpos = event.motion.xrel;
                if (oldx != 0)
                    xpos = oldx - event.motion.xrel;

                std::cout << "xpos = " << xpos << " read pos: " << event.motion.x << " increase angle by " <<
                mouseSpeed * (1. / fps) * xpos << std::endl;

                horizontalAngle += mouseSpeed * (1. / fps) * xpos;
                verticalAngle   += mouseSpeed * (1. / fps) * ypos;

                std::cout << "angle:" << horizontalAngle << std::endl;

                oldx = oldx + xpos;
            }
        } // end event polling

        // if (xpos)
        // oldx = oldx + xpos;
        // oldy = oldy + ypos;

        delta_tick = clock() - current_tick;
        if (delta_tick > 0)
        fps = CLOCKS_PER_SEC / delta_tick;
        if (frame > (size_t) fps / 2)
        {
            frame = 0;
            std::string title = "FPS: " + std::to_string(fps) + " x=" + std::to_string(oldx);
            // glfwSetWindowTitle(_window, title.c_str());
        }
        frame++;
    }
}
