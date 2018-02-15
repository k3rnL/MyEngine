/**
 * @Date:   2018-02-14T23:13:07+01:00
 * @Last modified time: 2018-02-14T23:15:22+01:00
 */

#include "fse/Scene/DynamicScene.hpp"

using namespace fse::scene;

DynamicScene::DynamicScene() : dispatcher(&collisionConfiguration), dynamicsWorld(&dispatcher, &broadphase, &solver, &collisionConfiguration)
{
    dynamicsWorld.setGravity(btVector3(0, -10, 0));
	btCollisionShape* groundShape = new btStaticPlaneShape(btVector3(0, 1, 0), 1);
	btDefaultMotionState* groundMotionState =
		new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, -1, 0)));
	btRigidBody::btRigidBodyConstructionInfo
		groundRigidBodyCI(0, groundMotionState, groundShape, btVector3(0, 0, 0));
	btRigidBody* groundRigidBody = new btRigidBody(groundRigidBodyCI);
	dynamicsWorld.addRigidBody(groundRigidBody);
}

DynamicScene::~DynamicScene() {

}

object::DynamicObject        *DynamicScene::addObject(std::string const &file) {
	object::DynamicObject                  *obj;

	if (mesh_catalog.find(file) != mesh_catalog.end())
		obj = new object::DynamicObject(mesh_catalog.find(file)->second);
	else
		obj = createObject(file);
	nodes.push_back(obj);
	dynamicsWorld.addRigidBody(obj->body);
	return (obj);
}

object::DynamicObject        *DynamicScene::createObject(std::string const &file) {
	object::Object *obj = SceneManager::createObject(file);
	object::DynamicObject *dyn_obj = new object::DynamicObject(*obj);

	delete obj;
	return dyn_obj;
}

void	DynamicScene::update(float deltaT) {
	dynamicsWorld.stepSimulation(deltaT);
}