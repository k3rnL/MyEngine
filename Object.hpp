/**
 * @Author: danielb
 * @Date:   2017-07-24T01:15:02+02:00
 * @Last modified by:   daniel_b
 * @Last modified time: 2017-09-06T02:30:46+02:00
 */

#ifndef OBJECT_HPP
#define OBJECT_HPP

#include <list>
#include <memory>

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

#include <GL/glew.h>

#include "Shader.hpp"
#include "Material.hpp"
#include "Scene/INode.hpp"
#include "GLItem/Mesh.hpp"

namespace mxe {
    namespace scene {
        namespace object {

            class Object : public INode
            {
                friend class Wavefront;
            public:
                Object();

                virtual ~Object();

                virtual void    draw(renderer::ObjectsToDrawCallback &callback,
                                     const glm::mat4 &transform);

                virtual INode   *clone();

                std::shared_ptr<Material>   getMaterial();
                void                        applyMaterial(std::shared_ptr<Material> mat);

                virtual void                setPosition(const glm::vec3 &pos);

                std::shared_ptr<gl_item::Mesh> getMesh() { return (_mesh); }

            protected:

              std::shared_ptr<mxe::gl_item::Mesh>  _mesh;

              GLuint          _buffer_vertex_id;
              GLuint          _buffer_normal_id;
              GLuint          _buffer_uv_id;
              GLsizei         _buffer_size;

              size_t          _nb_vertex;

              std::shared_ptr<Material>        _material;

            private:
              void              enableAttribute(GLuint buffer, GLuint attr, GLuint size);
            };

            typedef std::list<Object *> ObjectList;

        } // object
    } // scene
} // mxe

#endif
