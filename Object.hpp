/**
 * @Author: danielb
 * @Date:   2017-07-24T01:15:02+02:00
 * @Last modified by:   daniel_b
 * @Last modified time: 2017-07-30T20:43:08+02:00
 */

#ifndef OBJECT_HPP
#define OBJECT_HPP

#include <list>

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

#include <GL/glew.h>

#include "Shader.hpp"
#include "Material.hpp"

namespace mxe {
    namespace scene {
        namespace object {

            class Object
            {
            public:
                Object();

                virtual ~Object();

                virtual void draw(const glm::mat4 &projection, const glm::mat4 &view, const glm::vec3 &cam_pos);

                glm::vec3   position;
                glm::vec3   rotation;

            protected:
                GLuint      _buffer_vertex_id;
                GLuint      _buffer_normal_id;
                GLsizei     _buffer_size;

                size_t      _nb_vertex;

                Material    _material;

            private:
              void          enableAttribute(GLuint buffer, GLuint attr);
            };

            typedef std::list<Object *> ObjectList;

        } // object
    } // scene
} // mxe

#endif
