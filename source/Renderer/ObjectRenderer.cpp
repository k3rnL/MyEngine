/**
 * @Author: daniel_b
 * @Date:   2017-08-30T00:27:25+02:00
 * @Last modified by:   daniel_b
 * @Last modified time: 2017-11-15T01:41:54+01:00
 */



#include "fse/Renderer/ObjectRenderer.hpp"
#include <map>
using namespace fse::renderer;

ObjectRenderer::ObjectRenderer()
    // ObjectRenderer::ObjectRenderer(const glm::mat4 &projection) :
    //     _projection(projection)
{
    _shadow = 0;
}

void    ObjectRenderer::addNode(scene::INode *node)
{
    node->draw(_callback, glm::mat4(1.0));
}

void    ObjectRenderer::drawAll()
{
    auto &objects = _callback.objects;

    for (auto shader_to_mat : objects)
    {
        ShaderManager::getInstance().useShader(shader_to_mat.first);
      // shader_to_mat.first->useProgram();
      for (auto mat_to_obj : shader_to_mat.second)
      {
        mat_to_obj.first->useMaterial();
        for (auto mesh : mat_to_obj.second)
        {
          mesh.first->bindToShader();
          for (auto transform : mesh.second)
          {
            // shaders.getActualShader()->setUniformValue(glm::vec3(200, 100, 100), "mt_data.diffuse_color");
            ShaderManager::getInstance().getActualShader()->setUniformValue(transform, "model_view");
            if (_shadow) {
                _shadow->activate(1);
                ShaderManager::getInstance().getActualShader()->setUniformValue(1, "shadow_map");
            }
            glDrawElements(GL_TRIANGLES, mesh.first->getElementCount(), GL_UNSIGNED_INT, 0);
          }
          mesh.first->detachFromShader();
        }
      }
    }
}

void    ObjectRenderer::drawAll(std::shared_ptr<gl_item::Shader> shader)
{
    auto &objects = _callback.objects;

    for (auto shader_to_mat : objects)
    {
      ShaderManager::getInstance().useShader(shader);
      for (auto mat_to_obj : shader_to_mat.second)
      {
        // mat_to_obj.first->useMaterial();
        for (auto mesh : mat_to_obj.second)
        {
          mesh.first->bindToShader();
          for (auto transform : mesh.second)
          {
            // shaders.getActualShader()->setUniformValue(glm::vec3(200, 100, 100), "mt_data.diffuse_color");
            ShaderManager::getInstance().getActualShader()->setUniformValue(transform, "model_view");
            if (_shadow) {
                _shadow->activate(1);
                ShaderManager::getInstance().getActualShader()->setUniformValue(1, "shadow_map");
            }
            glDrawElements(GL_TRIANGLES, mesh.first->getElementCount(), GL_UNSIGNED_INT, 0);
          }
          mesh.first->detachFromShader();
        }
      }
    }
}

void    ObjectRenderer::setShadowMap(std::shared_ptr<gl_item::Texture> texture) {
    _shadow = texture;
}

void    ObjectRenderer::clean()
{
    _callback.objects.clear();
}
