/**
 * @Author: daniel_b
 * @Date:   2017-09-06T01:31:46+02:00
 * @Last modified by:
 * @Last modified time: 2018-02-14T04:16:38+01:00
 */



#include "fse/Renderer/ObjectsToDrawCallback.hpp"

using namespace fse::renderer;

void    ObjectsToDrawCallback::addObject(std::shared_ptr<fse::scene::object::Material>  mat,
                                         std::shared_ptr<fse::gl_item::Mesh>            mesh,
                                         const glm::mat4								&transform,
                                         void											*node)
{
  objects_to_draw[mat->getShader()][mat][mesh].push_back(std::make_tuple(transform, node));
}
