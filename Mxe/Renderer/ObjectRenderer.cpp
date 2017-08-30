/**
 * @Author: daniel_b
 * @Date:   2017-08-30T00:27:25+02:00
 * @Last modified by:   daniel_b
 * @Last modified time: 2017-08-30T05:27:23+02:00
 */



#include "Mxe/Renderer/ObjectRenderer.hpp"
#include <map>
using namespace mxe::renderer;

ObjectRenderer::ObjectRenderer(const glm::mat4 &projection) :
    _projection(projection)
{

}

void    ObjectRenderer::drawAll(ShaderManager &shaders)
{
    for (auto mat_to_obj : objects)
    {
        mat_to_obj.first->applyMaterial(shaders.getActualShader());
        for (auto mesh : mat_to_obj.second)
        {
            mesh.first->bindToShader();
            for (auto transform : mesh.second)
            {
                // shaders.getActualShader()->setUniformValue(glm::vec3(200, 100, 100), "mt_data.diffuse_color");

                shaders.getActualShader()->setUniformValue(transform, "model_view");
                glDrawArrays(GL_TRIANGLES, 0, mesh.first->_nb_vertex);
            }
        }
    }
}

void    ObjectRenderer::addObject(std::shared_ptr<scene::object::Material>  mat,
                                  std::shared_ptr<gl_item::Mesh>            mesh,
                                  const glm::mat4                           &transform)
{
    auto material_to_models = objects.insert(std::make_pair(mat, std::list<std::pair<std::shared_ptr<gl_item::Mesh>,
                                                                            std::list<glm::mat4>>>()));
    auto mat_to_models_it = material_to_models.first;

    auto it = mat_to_models_it->second.begin();
    while (it != mat_to_models_it->second.end())
    {
        if (it->first == mesh)
        {
            it->second.push_back(transform);
            break;
        }
    }
    if (it == mat_to_models_it->second.end())
    {
        mat_to_models_it->second.push_back(std::make_pair(mesh, std::list<glm::mat4>()));
        mat_to_models_it->second.back().second.push_back(transform);
    }
}


void    ObjectRenderer::clean()
{
    objects.clear();
}
