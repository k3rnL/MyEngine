/**
 * @Author: daniel_b
 * @Date:   2017-07-25T00:25:33+02:00
 * @Last modified by:   daniel_b
 * @Last modified time: 2017-08-23T19:10:42+02:00
 */

#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include <string>
#include <memory>

#include <GL/glew.h>
#include <glm/glm.hpp>

#include "Shader.hpp"

namespace mxe {
  namespace scene {
    namespace object {

      class Texture
      {
      public:
        glm::vec2     Size;
        std::string   Name;
        GLuint        Texture_id;
        unsigned char *Texture_data;

      };

      class Material
      {
      public:
        Material();
        Material(Material &mat);
        ~Material();

        void        setColor(const float &r, const float &g, const float &b);

        void        applyMaterial(Shader *shader);
        void        setTexture(const std::string &file);

        Material    &operator=(Material &mat);
      private:
        std::shared_ptr<Texture>               _texture;

        glm::vec3             _color;
      };

    } // object
  } // scene
} // mxe

#endif
