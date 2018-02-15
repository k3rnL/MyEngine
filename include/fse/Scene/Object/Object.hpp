/**
 * @Author: danielb
 * @Date:   2017-07-24T01:15:02+02:00
 * @Last modified by:
 * @Last modified time: 2018-02-14T04:38:32+01:00
 */

#ifndef OBJECT_HPP
#define OBJECT_HPP

#include <list>
#include <memory>

#include <glm/glm.hpp>
#include "glm/gtc/matrix_transform.hpp"
#include <glm/gtc/quaternion.hpp>

#include <GL/glew.h>

#include "fse/Export.hpp"
#include "fse/Material.hpp"
#include "fse/Scene/INode.hpp"
#include "fse/GLItem/Shader.hpp"
#include "fse/GLItem/Mesh.hpp"

namespace fse {
    namespace scene {
        namespace object {

            class FSE_API_EXPORT Object : public INode
            {
                friend class Wavefront;
            public:
                Object();
				Object(std::shared_ptr<gl_item::Mesh> mesh);

                virtual ~Object();

                virtual void    draw(renderer::ObjectsToDrawCallback &callback,
                                     const glm::mat4 &transform);

                virtual INode   *clone();

                std::shared_ptr<Material>   getMaterial();
                void                        applyMaterial(std::shared_ptr<Material> mat);

                virtual void                setPosition(const glm::vec3 &pos);

				virtual std::shared_ptr<gl_item::Mesh>	getMesh() const	{ return (_mesh); }
				virtual void							setMesh(std::shared_ptr<gl_item::Mesh> mesh)
																		{ _mesh = mesh; }

            protected:

              std::shared_ptr<fse::gl_item::Mesh>  _mesh;
              std::shared_ptr<Material>        _material;

            };

            typedef std::list<Object *> ObjectList;

        } // object
    } // scene
} // fse

#endif
