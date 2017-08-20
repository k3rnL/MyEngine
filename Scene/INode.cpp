/**
 * @Author: daniel_b
 * @Date:   2017-08-01T00:33:57+02:00
 * @Last modified by:   daniel_b
 * @Last modified time: 2017-08-18T15:50:58+02:00
 */



#include "Scene/INode.hpp"

using namespace mxe::scene;

void    INode::draw(const glm::mat4 &projection, const glm::mat4 &view, const glm::mat4 &transform, const glm::vec3 &cam_pos)
{
    for (auto child : childs)
    {
        child->draw(projection, view, transform, cam_pos);
    }
}

void    INode::setPosition(const glm::vec3 &position) {
  _position = position;
}

void    INode::setRotation(const glm::vec3 &rotation) {
  _rotation = rotation;
}

glm::vec3   &INode::getPosition() {
  return (_position);
}

glm::vec3   &INode::getRotation() {
  return (_rotation);
}
