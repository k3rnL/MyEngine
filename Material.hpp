/**
 * @Author: daniel_b
 * @Date:   2017-07-25T00:25:33+02:00
 * @Last modified by:   daniel_b
 * @Last modified time: 2017-07-27T01:42:25+02:00
 */

#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include <GL/glew.h>
#include <glm/glm.hpp>

#include "Shader.hpp"

namespace mxe {
  namespace scene {
    namespace object {

      class Material
      {
      public:
        Material();

        void        setColor(const float &r, const float &g, const float &b);

        void        applyMaterial();

        Shader      &getShader();

      private:
        Shader      *_shader;

        glm::vec3   _color;
      };

    } // object
  } // scene
} // mxe

#endif
