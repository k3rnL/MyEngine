/**
 * @Author: danielb
 * @Date:   2017-07-23T04:58:34+02:00
 * @Last modified by:   danielb
 * @Last modified time: 2017-07-24T02:10:37+02:00
 */



#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <GL/glew.h>

#include "Shader.hpp"
#include "Object.hpp"

namespace mxe {
    namespace scene {
        namespace object {

            class Triangle : public Object
            {
            public:
                Triangle(const glm::vec3 &v1, const glm::vec3 &v2, const glm::vec3 &v3);
            };

        } // object
    } // scene
} // mxe

#endif
