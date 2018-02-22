/**
 * @Author: danielb
 * @Date:   2017-07-24T01:16:33+02:00
 * @Last modified by:
 * @Last modified time: 2018-02-14T04:17:17+01:00
 */


#include "fse/Scene/Object/Object.hpp"

#define GLM_ENABLE_EXPERIMENTAL
	#include <glm/ext.hpp>

using namespace fse::scene::object;

Object::Object()
{
    _material = std::make_shared<Material>();
    _mesh = 0;
}

Object::Object(std::shared_ptr<fse::gl_item::Mesh> mesh) {
	_material = std::make_shared<Material>();
	_mesh = mesh;
}

Object::~Object()
{

}

fse::scene::INode       *Object::clone()
{
    Object           *node = new Object();

    node->_scale = _scale;
    node->_mesh = this->_mesh;
    node->_material = _material;
    return (node);
}

void            Object::setPosition(const glm::vec3 &position)
{
    _position = position;
}

void                Object::draw(fse::renderer::ObjectsToDrawCallback &callback,
                                 const glm::mat4 &transform)
{
    glm::mat4   node_transform;
    glm::quat   quat(_rotation);
	glm::mat4	translation = glm::translate(_position);
	glm::mat4	scale = glm::scale(_scale);

	node_transform = transform * translation * scale * glm::orientate4(getRotation());
    callback.addObject(_material, _mesh, node_transform, this);

    for (auto child : childs)
    {
        child->draw(callback, node_transform);
    }
}

std::shared_ptr<Material>    Object::getMaterial()
{
    return (_material);
}

void    Object::applyMaterial(std::shared_ptr<Material> mat)
{
  _material = mat;
}
