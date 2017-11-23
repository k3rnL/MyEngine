/**
 * @Author: danielb
 * @Date:   2017-07-24T02:31:09+02:00
 * @Last modified by:   daniel_b
 * @Last modified time: 2017-11-22T01:01:11+01:00
 */



#include "fse/Renderer/Renderer.hpp"

using namespace fse;

Renderer::Renderer(Window &window) :
    _window(window), _object_renderer()
{
    projection = glm::perspective<float>(45, // fov
                    (float) window.getWidth() / (float) window.getHeight(), // ratio
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

bool GetFirstNMessages(GLuint numMsgs)
{
	GLint maxMsgLen = 0;
	glGetIntegerv(GL_MAX_DEBUG_MESSAGE_LENGTH, &maxMsgLen);

	std::vector<GLchar> msgData(numMsgs * maxMsgLen);
	std::vector<GLenum> sources(numMsgs);
	std::vector<GLenum> types(numMsgs);
	std::vector<GLenum> severities(numMsgs);
	std::vector<GLuint> ids(numMsgs);
	std::vector<GLsizei> lengths(numMsgs);

	GLuint numFound = glGetDebugMessageLog(numMsgs, msgData.size(), &sources[0], &types[0], &ids[0], &severities[0], &lengths[0], &msgData[0]);

    if (numFound == 0)
        return false;

	sources.resize(numFound);
	types.resize(numFound);
	severities.resize(numFound);
	ids.resize(numFound);
	lengths.resize(numFound);

	std::vector<std::string> messages;
	messages.reserve(numFound);

	std::vector<GLchar>::iterator currPos = msgData.begin();
	for(size_t msg = 0; msg < lengths.size(); ++msg)
	{
		std::cout << std::string(currPos, currPos + lengths[msg] - 1) << "\n";
		currPos = currPos + lengths[msg];
	}
    return true;
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

    // scene.getLight()->updateShadowMap(_object_renderer);

    ShaderManager::getInstance().setUniformValue(time_i+=1.0/_fps.getFrameRate(), "time");

    ShaderManager::getInstance().setUniformValue(projection, "projection");
    ShaderManager::getInstance().setUniformValue(view, "view");

    ShaderManager::getInstance().setUniformValue(scene.getLight()->getPosition(), "light_pos");
    ShaderManager::getInstance().setUniformValue(scene.getLight()->getMVP(), "light_mvp");

    ShaderManager::getInstance().setUniformValue(scene.camera->getPosition(), "camera_position");

    glViewport(0, 0, _window.getWidth(), _window.getHeight());
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    // glEnable(GL_MULTISAMPLE);
    //  glHint(GL_MULTISAMPLE_FILTER_HINT_NV, GL_NICEST);
    // glEnable(GL_DEBUG_OUTPUT);
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
