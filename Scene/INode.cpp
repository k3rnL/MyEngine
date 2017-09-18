/**
 * @Author: daniel_b
 * @Date:   2017-08-01T00:33:57+02:00
 * @Last modified by:   daniel_b
 * @Last modified time: 2017-09-07T01:11:07+02:00
 */



#include "Scene/INode.hpp"

using namespace mxe::scene;

unsigned int g_count = 0;

// void    INode::draw(ShaderManager &shaders, const glm::mat4 &projection, const glm::mat4 &view, const glm::mat4 &transform, const glm::vec3 &cam_pos)
// {
//     for (auto child : childs)
//     {
//         child->draw(shaders, projection, view, transform, cam_pos);
//     }
// }

INode::INode() : _scale(1.0, 1.0, 1.0)
{

}

INode               *INode::clone()
{
    INode           *node = new INode();

    node->_position = _position;
    node->_rotation = _rotation;
    node->_scale = _scale;
    return (node);
}

void                INode::draw(renderer::ObjectsToDrawCallback &callback,
                                 const glm::mat4 &transform)
{
    glm::mat4   node_transform;
    glm::quat   quat(_rotation);

    node_transform = transform * glm::translate(_position) * glm::scale(_scale) * glm::toMat4(quat);
    for (auto child : childs)
    {
        child->draw(callback, node_transform);
    }
}

void    INode::setPosition(const glm::vec3 &position) {
  _position = position;
}

void    INode::setRotation(const glm::vec3 &rotation) {
  _rotation = rotation;
}

void    INode::setScale(const glm::vec3 &scale) {
    _scale = scale;
}

glm::vec3   &INode::getPosition() {
  return (_position);
}

glm::vec3   &INode::getRotation() {
  return (_rotation);
}

glm::vec3   &INode::getScale() {
    return (_scale);
}

void        INode::addChild(mxe::scene::INode *child) {
    childs.push_back(child);
}
