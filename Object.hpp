/**
 * @Author: danielb
 * @Date:   2017-07-24T01:15:02+02:00
 * @Last modified by:   daniel_b
 * @Last modified time: 2017-08-20T23:05:22+02:00
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
            public:
                Object();

                virtual ~Object();

                virtual void    draw(const glm::mat4 &projection, const glm::mat4 &view, const glm::mat4 &transform, const glm::vec3 &cam_pos);

                virtual INode   *clone() = 0;

                std::shared_ptr<Material>   getMaterial();
                void                        applyMaterial(std::shared_ptr<Material> mat);

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
