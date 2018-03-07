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
		class DynamicWorld;

        namespace object {

            class FSE_API_EXPORT DynamicObject : public Object
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
				virtual void			registerOnWorld(DynamicWorld *world);
				virtual void			unregisterOnWorld(DynamicWorld *world);

				virtual void	setMesh(std::shared_ptr<gl_item::Mesh> mesh);
            private:
				float					mass;

				btConvexHullShape		*shape;
				btRigidBody				*body;
				btDynamicsWorld			*world;

                class MotionState : public btMotionState
                {
                public:
					MotionState(DynamicObject &node) : node(node) { }
                    virtual ~MotionState() { }

                    virtual void getWorldTransform(btTransform &tr) const { 
						auto &pos = node.getPosition();
						tr.setOrigin(btVector3(pos.x, pos.y, pos.z));
					}

					btVector3 quatToEuler(btQuaternion quat) {
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

		class FSE_API_EXPORT DynamicWorld {
		public:
			virtual void	registerObject(object::DynamicObject *object) = 0;
			virtual void	unregisterObject(object::DynamicObject *object) = 0;
		};

	}
}

#endif /* end of include guard: FSE_DYNAMIC_OBJECT_HPP */
