/**
 * @Date:   2018-02-14T12:19:06+01:00
 * @Last modified time: 2018-02-14T23:15:15+01:00
 */

#ifndef FSE_DYNAMICSCENE_HPP
#define FSE_DYNAMICSCENE_HPP

#include <btBulletDynamicsCommon.h>

#include "fse/Scene/SceneManager.hpp"
#include "fse/Scene/Object/DynamicObject.hpp"

namespace fse {
    namespace scene {

        class FSE_API_EXPORT DynamicScene : public SceneManager
        {
        public:
            DynamicScene();
            virtual ~DynamicScene();

			virtual object::DynamicObject        *addObject(std::string const &file);
			virtual object::DynamicObject        *createObject(std::string const &file);

			virtual void						update(float deltaT);

        private:
            // Build the broadphase
			btDbvtBroadphase						broadphase;

            // Set up the collision configuration and dispatcher
            btDefaultCollisionConfiguration         collisionConfiguration;
            btCollisionDispatcher                   dispatcher;

            // The actual physics solver
            btSequentialImpulseConstraintSolver     solver;

            // The world.
            btDiscreteDynamicsWorld                 dynamicsWorld;
        };

    }
}

#endif /* end of include guard: FSE_DYNAMICSCENE_HPP */
