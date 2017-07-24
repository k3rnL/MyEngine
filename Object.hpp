/**
 * @Author: danielb
 * @Date:   2017-07-24T01:15:02+02:00
 * @Last modified by:   danielb
 * @Last modified time: 2017-07-24T02:05:03+02:00
 */

#ifndef OBJECT_HPP
#define OBJECT_HPP

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

#include <GL/glew.h>

#include "Shader.hpp"

namespace mxe {
    namespace scene {
        namespace object {

            class Object
            {
            public:
                Object();

                virtual ~Object();

                virtual void draw(Shader &shader, const glm::mat4 view);

                glm::vec3   position;

            protected:
                GLuint      _buffer_id;
                GLsizei     _buffer_size;
            };

        } // object
    } // scene
} // mxe

#endif
