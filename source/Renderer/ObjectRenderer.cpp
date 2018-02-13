/**
* @Author: daniel_b
* @Date:   2017-08-30T00:27:25+02:00
 * @Last modified by:
 * @Last modified time: 2018-02-12T04:06:45+01:00
*/



#include "fse/Renderer/ObjectRenderer.hpp"
#include <map>
using namespace fse::renderer;
using namespace fse::gl_item;

ObjectRenderer::ObjectRenderer()
{
    _shadow = 0;
    _depth = Texture::create(2048, 2048, Texture::DEPTH, Texture::DETPH_COMPONENT, Texture::FLOAT);

    _depth->bind();
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_R_TO_TEXTURE);
    _depth->unbind();
}

void    ObjectRenderer::addNode(fse::scene::INode *node)
{
    node->draw(_callback, glm::mat4(1.0f));
}

void    ObjectRenderer::drawAll(fse::gl_item::Shader::AttributeHolder &attribute,
                                std::shared_ptr<fse::gl_item::Shader> shader)
{
    auto &objects = _callback.objects;
	bool use_mesh_shader = shader == 0;

    for (auto shader_to_mat : objects)
    {
		if (use_mesh_shader) {
			shader = shader_to_mat.first;
		}
		shader->useProgram();
		attribute.apply(shader);
        for (auto mat_to_obj : shader_to_mat.second) {
            mat_to_obj.first->useMaterial(shader);
            for (auto mesh : mat_to_obj.second)
            {
                mesh.first->bindToShader(shader);
                for (auto transform : mesh.second)
                {
                    shader->setUniformValue(transform, "model_view");
                    if (_shadow) {
                        _shadow->activate(2);
                        shader->setUniformValue(2, "shadow_map");
                    }
                    glDrawElements(GL_TRIANGLES, (GLsizei) mesh.first->getElementCount(), GL_UNSIGNED_INT, 0);
                }
                mesh.first->detachFromShader();
            }
        }
    }
}

void    ObjectRenderer::setShadowMap(std::shared_ptr<fse::gl_item::Texture> texture) {
    _shadow = texture;
}

void    ObjectRenderer::clean()
{
    _callback.objects.clear();
}
