/**
 * @Author: daniel_b
 * @Date:   2017-08-01T00:33:57+02:00
 * @Last modified by:   daniel_b
 * @Last modified time: 2017-11-20T23:56:16+01:00
 */



#include "fse/Scene/INode.hpp"

using namespace fse::scene;

unsigned int g_count = 0;

// void    INode::draw(ShaderManager &shaders, const glm::mat4 &projection, const glm::mat4 &view, const glm::mat4 &transform, const glm::vec3 &cam_pos)
// {
//     for (auto child : childs)
//     {
//         child->draw(shaders, projection, view, transform, cam_pos);
//     }
// }

INode::INode() : _scale(1.0f, 1.0f, 1.0f),
				 _position(0.0f, 0.0f, 0.0f),
				 _rotation(0.0f, 0.0f, 0.0f)
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

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/ext.hpp>

void                INode::draw(fse::renderer::ObjectsToDrawCallback &callback,
                                 const glm::mat4 &transform)
{
    glm::mat4   node_transform;
	glm::mat4	translation; glm::translate(translation, _position);
	glm::mat4	scale; glm::scale(scale, _scale);
	
	node_transform = transform * translation * scale * glm::orientate4(getRotation());
    for (auto child : childs)
    {
		child->draw(callback, transform);
		//child->draw(callback, node_transform);
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

const std::list<INode *>    &INode::getChilds() const {
    return childs;
}

void        INode::addChild(fse::scene::INode *child) {
    childs.push_back(child);
}
