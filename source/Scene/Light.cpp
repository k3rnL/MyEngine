/**
* @Author: daniel_b
* @Date:   2017-11-13T02:59:18+01:00
 * @Last modified by:   daniel_b
 * @Last modified time: 2017-11-13T03:43:58+01:00
*/

#include "fse/Scene/Light.hpp"

using namespace fse::scene;
using namespace fse::gl_item;

Light::Light() {
    glGenFramebuffers(1, &_frame_buffer);
    glBindFramebuffer(GL_FRAMEBUFFER, _frame_buffer);

    _texture = Texture::create(1024, 1024, Texture::DEPTH16, Texture::FLOAT);
    _texture->bind();
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, _texture->getId(), 0);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

}

void    Light::updateShadowMap(fse::renderer::ObjectRenderer &obj_renderer) {
    glBindFramebuffer(GL_FRAMEBUFFER, _frame_buffer);
    glDrawBuffer(GL_NONE);
    glm::vec3 lightInvDir = glm::vec3(0.5f,2,2);

    // Compute the MVP matrix from the light's point of view
    glm::mat4 depthProjectionMatrix = glm::ortho<float>(-10,10,-10,10,-10,20);
    glm::mat4 depthViewMatrix = glm::lookAt(lightInvDir, glm::vec3(0,0,0), glm::vec3(0,1,0));
    glm::mat4 depthModelMatrix = glm::mat4(1.0);

    ShaderManager::getInstance().setUniformValue(depthProjectionMatrix, "projection");
    ShaderManager::getInstance().setUniformValue(depthViewMatrix, "view");
    ShaderManager::getInstance().setUniformValue(depthViewMatrix, "model_view");
    ShaderManager::getInstance().setUniformValue(1, "shadowing");

    obj_renderer.drawAll();

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

glm::mat4   Light::getMVP() {
    glm::vec3 lightInvDir = glm::vec3(0.5f,2,2);

 // Compute the MVP matrix from the light's point of view
 glm::mat4 depthProjectionMatrix = glm::ortho<float>(-10,10,-10,10,-10,20);
 glm::mat4 depthViewMatrix = glm::lookAt(lightInvDir, glm::vec3(0,0,0), glm::vec3(0,1,0));
 glm::mat4 depthModelMatrix = glm::mat4(1.0);
 glm::mat4 depthMVP = depthProjectionMatrix * depthViewMatrix * depthModelMatrix;

    return (depthMVP);
}

std::shared_ptr<fse::gl_item::Texture>  Light::getTexture() {
    return (_texture);
}
