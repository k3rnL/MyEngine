/**
 * @Date:   2018-02-14T04:57:11+01:00
 * @Last modified time: 2018-02-14T05:41:43+01:00
 */

#include "fse/Renderer/ObjectPicker.hpp"

using namespace fse::renderer;


GLuint GenerateColorTexture(unsigned int width, unsigned int height){
    GLuint texture_color;
	glGenTextures(1, &texture_color);
	glBindTexture(GL_TEXTURE_2D, texture_color);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
    return (texture_color);
}

GLuint GenerateDepthTexture(unsigned int width, unsigned int height){
    GLuint texture_depth;
	glGenTextures(1, &texture_depth);
	glBindTexture(GL_TEXTURE_2D, texture_depth);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT24, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, 0);
    return (texture_depth);
}


//Generate FBO and two empty textures
GLuint GenerateFBO(unsigned int width, unsigned int height){

    GLuint FBO;
    //Generate a framebuffer object(FBO) and bind it to the pipeline
    glGenFramebuffers(1, &FBO);
    glBindFramebuffer(GL_FRAMEBUFFER, FBO);

    GLuint texture_color = GenerateColorTexture(width, height);//generate empty texture
    GLuint texture_depth = GenerateDepthTexture(width, height);//generate empty texture

    //to keep track of our textures
    unsigned int attachment_index_color_texture = 0;


    glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + attachment_index_color_texture, texture_color, 0);
    glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, texture_depth, 0);//optional

	GLuint attach = GL_COLOR_ATTACHMENT0;
	glDrawBuffers(1, &attach);
    //Check for FBO completeness
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE){
    	std::cout << "Error! FrameBuffer is not complete" << std::endl;
    	std::cin.get();
    	std::terminate();
    }

    //unbind framebuffer
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    return (FBO);
}

fse::scene::object::Object   *ObjectPicker::pickObject(const glm::mat4 &projection, const glm::mat4 &view, int x, int y) {
	fse::gl_item::Shader::AttributeHolder attr;

	id_found = 0;
	shader->useProgram();
	attr.addUniform("projection", projection);
	attr.addUniform("view", view);
	attr.apply(shader);
	glClearColor(0, 0, 0, 1);
	drawAll(attr, shader);
	return (objects[id_found]);
}

ObjectPicker::ObjectPicker(unsigned int width, unsigned int height) : width(width), height(height)
{
    frame_buffer = GenerateFBO(width, height);
    shader = std::make_shared<gl_item::Shader>("shader/basic.vert", "shader/picker.frag");
}

ObjectPicker::~ObjectPicker() {

}

void    ObjectPicker::onDrawBegin() {
    glBindFramebuffer(GL_FRAMEBUFFER, frame_buffer);
	glViewport(0, 0, width, height);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glDrawBuffer(GL_COLOR_ATTACHMENT0);
	glEnable(GL_DEPTH_TEST);
	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS);
    id = 50;
}

void    ObjectPicker::onPreDrawItem(std::shared_ptr<fse::gl_item::Shader> shader,
                                    std::shared_ptr<fse::scene::object::Material> material,
                                    std::shared_ptr<fse::gl_item::Mesh> mesh,
                                    fse::scene::object::Object *object,
                                    glm::mat4 const &transform)
{
    shader->setUniformValue((int)id, "id");
    objects[id++] = object;
}

void    ObjectPicker::onDrawFinished() {
    unsigned int pixel;
    glReadBuffer((GLenum)GL_COLOR_ATTACHMENT0);
    glReadPixels(width/2, height/2, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, (GLvoid*) &pixel);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
	id_found = (pixel & 0xff00) >> 8;
}
