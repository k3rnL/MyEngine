/**
 * @Author: daniel_b
 * @Date:   2017-09-06T01:31:46+02:00
 * @Last modified by:   daniel_b
 * @Last modified time: 2017-09-18T16:28:09+02:00
 */



#include "Mxe/Renderer/ObjectsToDrawCallback.hpp"

using namespace mxe::renderer;

void    ObjectsToDrawCallback::addObject(std::shared_ptr<scene::object::Material>  mat,
                                         std::shared_ptr<gl_item::Mesh>            mesh,
                                         const glm::mat4                           &transform)
{
  objects[mat->getShader()][mat][mesh].push_back(transform);
}
