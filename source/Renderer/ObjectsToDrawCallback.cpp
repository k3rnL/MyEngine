/**
 * @Author: daniel_b
 * @Date:   2017-09-06T01:31:46+02:00
 * @Last modified by:   daniel_b
 * @Last modified time: 2017-11-13T00:46:54+01:00
 */



#include "fse/Renderer/ObjectsToDrawCallback.hpp"

using namespace fse::renderer;

void    ObjectsToDrawCallback::addObject(std::shared_ptr<fse::scene::object::Material>  mat,
                                         std::shared_ptr<fse::gl_item::Mesh>            mesh,
                                         const glm::mat4                           &transform)
{
  objects[mat->getShader()][mat][mesh].push_back(transform);
}
