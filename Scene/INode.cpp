/**
 * @Author: daniel_b
 * @Date:   2017-08-01T00:33:57+02:00
 * @Last modified by:   daniel_b
 * @Last modified time: 2017-08-01T00:35:23+02:00
 */



#include "Scene/INode.hpp"

using namespace mxe::scene;

void    INode::draw(const glm::mat4 &projection, const glm::mat4 &view, const glm::vec3 &cam_pos)
{
    for (auto child : childs)
    {
        child->draw(projection, view, cam_pos);
    }
}
