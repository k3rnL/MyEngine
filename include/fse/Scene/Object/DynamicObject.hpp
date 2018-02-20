/**
 * @Date:   2018-02-14T23:16:45+01:00
 * @Last modified time: 2018-02-14T23:28:10+01:00
 */

#ifndef FSE_DYNAMIC_OBJECT_HPP
#define FSE_DYNAMIC_OBJECT_HPP

#include <btBulletDynamicsCommon.h>

#include "fse/Scene/Object/Object.hpp"

btVector3 quatToEuler(btQuaternion quat);

namespace fse {
    namespace scene {
		class DynamicScene;
        namespace object {

            class DynamicObject : public Object
            {
            public:
				DynamicObject(float mass = 10);
				DynamicObject(const Object &object, float mass = 10);
                virtual ~DynamicObject();

				virtual void          setPosition(const glm::vec3 &position);
				virtual void          setScale(const glm::vec3 &scale);

				virtual void			addForce(const glm::vec3 &force);

				virtual void			wakeOnMovement();
				virtual void			wakeUp();
				virtual bool			isWake();

				virtual void	setMesh(std::shared_ptr<gl_item::Mesh> mesh);
            private:
				float					mass;

				btConvexHullShape		*shape;
				btRigidBody				*body;

                class MotionState : public btMotionState
                {
                public:
					MotionState(DynamicObject &node) : node(node) { }
                    virtual ~MotionState() { }

                    virtual void getWorldTransform(btTransform &tr) const { 
						auto &pos = node.getPosition();
						tr.setOrigin(btVector3(pos.x, pos.y, pos.z));
					}
                    virtual void setWorldTransform(const btTransform &tr) {
						const btVector3 &pos = tr.getOrigin();
						node._position = glm::vec3(pos[0], pos[1], pos[2]);
						btVector3 euler = quatToEuler(tr.getRotation());
						node.setRotation(glm::vec3(euler[0], euler[2], euler[1]));
					}

                private:
                    DynamicObject       &node;
                    btTransform         initial;
                };

				MotionState				motion;

				friend class fse::scene::DynamicScene;
            };

        }
    }
}

#endif /* end of include guard: FSE_DYNAMIC_OBJECT_HPP */
