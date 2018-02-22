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

        class FSE_API_EXPORT DynamicScene : public SceneManager, public DynamicWorld
        {
        public:
            DynamicScene();
            virtual ~DynamicScene();

			virtual void						addChild(INode *node);

			virtual object::Object				*addObject(std::string const &file);
			virtual object::DynamicObject       *addObject(std::string const &file, float mass);
			virtual object::Object				*createObject(std::string const &file);
			virtual object::DynamicObject		*createObject(std::string const &file, float mass);

			virtual void						update(float deltaT);
			virtual void						registerObject(object::DynamicObject *obj);
			virtual void						unregisterObject(object::DynamicObject *obj);

			void								drawPhysicsScene(const glm::mat4 &projection);

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

			class FSE_API_EXPORT DebugDrawer : public btIDebugDraw
			{
			public:
				DebugDrawer() : buffer(gl_item::Buffer<glm::vec3>::ArrayBuffer, fse::gl_item::Buffer<glm::vec3>::DynamicBuffer) {
					shader = std::make_shared<fse::gl_item::Shader>("shader/basic.vert", "shader/basic.frag");
					data.resize(2);
				}

				void		setView(const glm::mat4 &view, const glm::mat4 &projection) {
					attribute.addUniform("view", view);
					attribute.addUniform("model_view", glm::mat4(1.0f));
					attribute.addUniform("projection", projection);
				}

				virtual void drawLine(const btVector3& from, const btVector3& to, const btVector3& color)
				{
					data[0] = glm::vec3(from[0], from[1], from[2]);
					data[1] = glm::vec3(to[0], to[1], to[2]);
					buffer.send(data);

					shader->useProgram();
					shader->setAttribute(buffer, 0, 3);
					attribute.apply(shader);
					shader->setUniformValue(glm::vec3(color[0], color[1], color[2]), "color_in");
					glDrawArrays(GL_LINES, 0, 2);

				}
				virtual void drawContactPoint(const btVector3 &, const btVector3 &, btScalar, int, const btVector3 &) {}
				virtual void reportErrorWarning(const char *s) { std::cerr << "[Physics] " << s << "\n"; }
				virtual void draw3dText(const btVector3 &, const char *) {}
				virtual void setDebugMode(int p) {
					m = p;
				}
				gl_item::Shader::AttributeHolder		attribute;
				std::shared_ptr<fse::gl_item::Shader>	shader;
				fse::gl_item::Buffer<glm::vec3>			buffer;
				std::vector<glm::vec3>					data;
				virtual int getDebugMode(void) const { return 3; }
				int m;
			}				debug_drawer;
        };

    }
}

#endif /* end of include guard: FSE_DYNAMICSCENE_HPP */
