/**
 * @Author: danielb
 * @Date:   2017-07-24T01:15:02+02:00
 * @Last modified by:   daniel_b
 * @Last modified time: 2017-07-27T01:41:17+02:00
 */

#ifndef OBJECT_HPP
#define OBJECT_HPP

#include <list>

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

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

                virtual void draw(const glm::mat4 &projection, const glm::mat4 &view);

                glm::vec3   position;

            protected:
                GLuint      _buffer_vertex_id;
                GLuint      _buffer_normal_id;
                GLsizei     _buffer_size;

                size_t      _nb_vertex;

                Material    _material;
            };

            typedef std::list<Object *> ObjectList;

        } // object
    } // scene
} // mxe

#endif
