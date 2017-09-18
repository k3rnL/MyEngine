/**
 * @Author: daniel_b
 * @Date:   2017-09-06T01:31:46+02:00
 * @Last modified by:   daniel_b
 * @Last modified time: 2017-09-18T14:44:24+02:00
 */



#include "Mxe/Renderer/ObjectsToDrawCallback.hpp"

using namespace mxe::renderer;

void    ObjectsToDrawCallback::addObject(std::shared_ptr<scene::object::Material>  mat,
                                         std::shared_ptr<gl_item::Mesh>            mesh,
                                         const glm::mat4                           &transform)
{
    auto it_shader = objects.begin();
    while (it_shader != objects.end() && it_shader->first != mat->getShader())
        it_shader++;
    if (it_shader == objects.end())
    {
    }
        objects.insert(std::make_pair(mat->getShader(), std::make_pair(mat, std::list<std::pair<std::shared_ptr<gl_item::Mesh>,
                                                                            std::list<glm::mat4>>>())));


    auto it_mat = objects.begin();
    while (it_mat != objects.end() && it_mat->first != mat)
        it_mat++;

    if (it_mat == objects.end())
        objects.insert(std::make_pair(mat, std::list<std::pair<std::shared_ptr<gl_item::Mesh>,
                                                                            std::list<glm::mat4>>>()));

    auto it = objects[mat].begin();
    while (it != objects[mat].end())
    {
        if (it->first == mesh)
        {
            it->second.push_back(transform);
            break;
        }
        it++;
    }
    if (it == objects[mat].end())
    {
        objects[mat].push_back(std::make_pair(mesh, std::list<glm::mat4>()));
        objects[mat].back().second.push_back(transform);
    }
}
