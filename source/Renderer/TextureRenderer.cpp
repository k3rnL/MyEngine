/**
 * @Author: daniel_b
 * @Date:   2017-12-16T01:38:34+01:00
 * @Last modified by:   daniel_b
 * @Last modified time: 2017-12-16T04:05:40+01:00
 */

#include "fse/Renderer/TextureRenderer.hpp"

using namespace fse;
using namespace fse::gl_item;
using namespace fse::renderer;

TextureRenderer::TextureRenderer(Window &win) :
    _window(win)
{
    _shader = std::make_shared<Shader>();
    _texture = Texture::create(win.getWidth(), win.getHeight(), Texture::RGBA32F, Texture::RGBA, Texture::FLOAT);
    // Enable depth test
    glEnable(GL_DEPTH_TEST);
    // Accept fragment if it closer to the camera than the former one
    glDepthFunc(GL_LESS);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    mesh.addVertex(glm::vec3(-1, -1, 0));
    mesh.addVertex(glm::vec3(1, -1, 0));
    mesh.addVertex(glm::vec3(-1, 1, 0));
    mesh.addVertex(glm::vec3(1, 1, 0));

    mesh.addUV(glm::vec2(0, 0));
    mesh.addUV(glm::vec2(1, 0));
    mesh.addUV(glm::vec2(0, 1));
    mesh.addUV(glm::vec2(1, 1));

    mesh.addFace(glm::vec3(2, 1, 0));
    mesh.addFace(glm::vec3(1, 3, 2));

    mesh.finish();

    _shader->addShader("shader/texture.vert", Shader::VERTEX);
    _shader->addShader("shader/texture.frag", Shader::FRAGMENT);
    _shader->link();
}

void    TextureRenderer::setTexture(std::shared_ptr<gl_item::Texture> texture)
{
    _texture = texture;
}

std::shared_ptr<gl_item::Texture>   TextureRenderer::getTexture() {
    return (_texture);
}

void    TextureRenderer::draw()
{
    glm::mat4 projection = glm::perspective<float>(45, // fov
                    (float) _window.getWidth() / (float) _window.getHeight(), // ratio
                    0.1, 100.0); // near / far
    glm::mat4 view = glm::lookAt(glm::vec3(0, 0, -1), glm::vec3(0), glm::vec3(0, 1, 0));
    glm::mat4 mat = projection * view * glm::mat4(1.);

    _shader->useProgram();
    _shader->setUniformValue(view, "view");
    _shader->setUniformValue(projection, "projection");
    mesh.bindToShader(_shader);
    _texture->activate(0);
    _texture->bind();
    glDrawElements(GL_TRIANGLES, mesh.getElementCount(), GL_UNSIGNED_INT, 0);
    mesh.detachFromShader();
    _window.flipScreen();

}
