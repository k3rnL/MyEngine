/**
 * @Date:   2018-02-14T12:18:30+01:00
 * @Last modified time: 2018-02-14T12:18:30+01:00
 */

#include "fse/Scene/Object/DynamicObject.hpp"

using namespace fse::scene::object;

DynamicObject::~DynamicObject() {
	delete body;
	delete shape;
}

DynamicObject::DynamicObject(float mass) : motion(*this) {
	shape = 0;
	body = 0;
	this->mass = mass;
}

DynamicObject::DynamicObject(const Object &object, float mass) : motion(*this) {
	shape = 0;
	body = 0;
	this->mass = mass;
	setMesh(object.getMesh());
}

void			DynamicObject::addForce(const glm::vec3 &force) {
	if (body)
		body->applyForce(btVector3(force.x, force.y, force.z), btVector3(0, 0, 0));
}

void          DynamicObject::setPosition(const glm::vec3 &position) {
	INode::setPosition(position);
	body->getWorldTransform().setOrigin(btVector3(position.x, position.y, position.z));
}

void          DynamicObject::setScale(const glm::vec3 &s) {
	INode::setScale(s);
	shape->setLocalScaling(btVector3(s.x, s.y, s.z));
	body->activate(true);
}

void	DynamicObject::wakeOnMovement() {
	if (body)
		body->forceActivationState(WANTS_DEACTIVATION);
}

void	DynamicObject::wakeUp() {
	if (body)
		body->forceActivationState(ACTIVE_TAG);
}

bool	DynamicObject::isWake() {
	if (body)
		return (body->isActive());
	return (false);
}

void	DynamicObject::setMesh(std::shared_ptr<fse::gl_item::Mesh> mesh) {
	btConvexHullShape *new_shape = new btConvexHullShape((btScalar *)&mesh->getVertexes()[0], mesh->getVertexes().size(), 12);
	
	/*for (auto v : mesh->getVertexes()) {
		new_shape->addPoint(btVector3(v.x, v.y, v.z));
	}*/

	/*/create a hull approximation
	btShapeHull* hull = new btShapeHull(&shape);
	btScalar margin = originalConvexShape->getMargin();
	hull->buildHull(margin);
	btConvexHullShape* simplifiedConvexShape = new btConvexHullShape(hull->getVertexPointer(), hull->numVertices());*/
	new_shape->setMargin(0);
	new_shape->setLocalScaling(btVector3(getScale().x, getScale().y, getScale().z));
	if (shape)
		delete shape;
	shape = new_shape;

	if (!body) {
		btRigidBody::btRigidBodyConstructionInfo
			rigidBodyCI(0, &motion, shape, btVector3(0, 0, 0));
		body = new btRigidBody(rigidBodyCI);
	}
	
	body->setCollisionShape(shape);
	btVector3 fallInertia(0, 0, 0);
	shape->calculateLocalInertia(mass, fallInertia);
	body->setMassProps(mass, fallInertia);

	this->_mesh = mesh;
}

btVector3 quatToEuler(btQuaternion quat)
{
	float  heading, attitude, bank;
	btQuaternion q1;
	q1[0] = quat.getX();
	q1[1] = quat.getY();
	q1[2] = quat.getZ();
	q1[3] = quat.getW();
	double test = q1[0] * q1[1] + q1[2] * q1[3];
	if (test > 0.499) { // singularity at north pole
		heading = 2 * atan2(q1[0], q1[3]);
		attitude = M_PI / 2;
		bank = 0;
		return btVector3(0, 0, 0);
	}
	if (test < -0.499) { // singularity at south pole
		heading = -2 * atan2(q1[0], q1[3]);
		attitude = -M_PI / 2;
		bank = 0;
		return  btVector3(0, 0, 0);
	}
	double sqx = q1[0] * q1[0];
	double sqy = q1[1] * q1[1];
	double sqz = q1[2] * q1[2];
	heading = atan2(2 * q1[1] * q1[3] - 2 * q1[0] * q1[2], 1 - 2 * sqy - 2 * sqz);
	attitude = asin(2 * test);
	bank = atan2(2 * q1[0] * q1[3] - 2 * q1[1] * q1[2], 1 - 2 * sqx - 2 * sqz);
	btVector3 vec(bank, heading, attitude);
	return vec;
}