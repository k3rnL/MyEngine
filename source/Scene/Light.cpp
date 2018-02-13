/**
* @Author: daniel_b
* @Date:   2017-11-13T02:59:18+01:00
 * @Last modified by:   daniel_b
 * @Last modified time: 2017-11-22T00:59:07+01:00
*/

#include "fse/Scene/Light.hpp"

using namespace fse::scene;
using namespace fse::gl_item;

Light::Light() {
    setQuality(12);

    glGenFramebuffers(1, &_frame_buffer);
    glBindFramebuffer(GL_FRAMEBUFFER, _frame_buffer);

    _texture = Texture::create(_quality, _quality, Texture::DEPTH, Texture::DETPH_COMPONENT, Texture::FLOAT);

    _texture->bind();
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_R_TO_TEXTURE);

    _texture->unbind();
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, _texture->getId(), 0);

    glDrawBuffer(GL_NONE);

    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    {
        std::cout << "[ERROR] Cannot create light\n";
    }
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    // Compute the MVP matrix from the light's point of view
    // glm::mat4 depthProjectionMatrix = glm::ortho<float>(-10,10,-10,10,-10,20);
    _projection = glm::perspective<float>(65, // fov
                    (float) 256 / (float) 256, // ratio
                    0.1f, 100.0f); // near / far

    _view = glm::lookAt(getPosition(), getPosition() + glm::vec3(0,-1,0), glm::vec3(0,0,1));

    _shader = ShaderManager::getInstance().addShader("shadow");
}

void    Light::updateShadowMap(fse::renderer::ObjectRenderer &obj_renderer) {
    glBindFramebuffer(GL_FRAMEBUFFER, _frame_buffer);
    // glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, _texture->getId(), 0);
    glClear(GL_DEPTH_BUFFER_BIT);

    glm::vec3 lightInvDir = glm::vec3(0.5f,2,2);

    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    {
        std::cout << "[ERROR] Cannot create light\n";
    }

    _view = glm::lookAt(getPosition(), getPosition() - glm::vec3(0,1,0), glm::vec3(0,0,-1));

	_shader->useProgram();
    // auto default_shader = ShaderManager::getInstance().getDefaultShader();
    // ShaderManager::getInstance().useShader(default_shader);
    // _shader->setUniformValue(depthProjectionMatrix, "proj_matrix");
    // _shader->setUniformValue(depthViewMatrix, "view_matrix");
	Shader::AttributeHolder attr;

	attr.addUniform("projection", _projection);
	attr.addUniform("view", _view);

    GLenum err;
    while((err = glGetError()) != GL_NO_ERROR)
    {
        std::cout << "[ERROR] " << __FILE__ << ":" << __LINE__ << " gl err = " << err << "\n";
    }
    // // Enable depth test
    // glEnable(GL_DEPTH_TEST);
    // // Accept fragment if it closer to the camera than the former one
    // glDepthFunc(GL_LESS);
    //
    glEnable(GL_CULL_FACE);
    glCullFace(GL_FRONT);
    glViewport(0, 0, (GLsizei) _quality, (GLsizei) _quality);

    obj_renderer.drawAll(attr, _shader);
    // obj_renderer.drawAll();

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void        Light::setQuality(unsigned int q) {
    _quality = (size_t) std::pow(2,q);
}

glm::mat4   Light::getMVP() {
    // glm::vec3 lightInvDir = glm::vec3(0.5f,2,2);
    //
    // // Compute the MVP matrix from the light's point of view
    // glm::mat4 depthProjectionMatrix = glm::perspective<float>(45, // fov
    //                 (float) 1024 / (float) 1024, // ratio
    //                 0.1, 100.0); // near / far
    // glm::mat4 depthViewMatrix = glm::lookAt(getPosition(), getPosition() + glm::vec3(0,-1,0), glm::vec3(0,0,1));
    // glm::mat4 depthModelMatrix = glm::mat4(1.0);
    // glm::mat4 depthMVP = depthProjectionMatrix * depthViewMatrix * depthModelMatrix;
    glm::mat4 biasMatrix(
    0.5, 0.0, 0.0, 0.0,
    0.0, 0.5, 0.0, 0.0,
    0.0, 0.0, 0.5, 0.0,
    0.5, 0.5, 0.5, 1.0
    );
    return (biasMatrix * _projection * _view);
}

std::shared_ptr<fse::gl_item::Texture>  Light::getTexture() {
    return (_texture);
}

void        Light::setView(const glm::mat4 &view) {
    _view = view;
}

glm::mat4   &Light::getProjection() {
    return (_projection);
}

glm::mat4   &Light::getView() {
    return (_view);
}
