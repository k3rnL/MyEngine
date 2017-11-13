/**
 * @Author: daniel_b
 * @Date:   2017-07-25T00:25:33+02:00
 * @Last modified by:   daniel_b
 * @Last modified time: 2017-11-13T00:46:13+01:00
 */

#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include <string>
#include <memory>

#include <GL/glew.h>
#include <glm/glm.hpp>

#include "fse/GLItem/Shader.hpp"
#include "fse/ShaderManager.hpp"

namespace fse {
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

        void            setColor(const float &r, const float &g, const float &b);
        void            setTexture(const std::string &file);
        void            setShader(std::shared_ptr<gl_item::Shader> shader);

        std::shared_ptr<gl_item::Shader>     getShader();

        virtual void    useMaterial();

        Material        &operator=(Material &mat);

        protected:
          std::shared_ptr<Texture>          _texture;
          std::shared_ptr<gl_item::Shader>  _shader;

          glm::vec3                         _color;
      };

    } // object
  } // scene
} // fse

#endif
