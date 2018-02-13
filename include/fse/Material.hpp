/**
 * @Author: daniel_b
 * @Date:   2017-07-25T00:25:33+02:00
 * @Last modified by:
 * @Last modified time: 2018-02-05T02:50:47+01:00
 */

#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include <string>
#include <memory>

#include <GL/glew.h>
#include <glm/glm.hpp>

#include "fse/Export.hpp"
#include "fse/GLItem/Shader.hpp"
#include "fse/GLItem/Texture.hpp"
#include "fse/ShaderManager.hpp"

namespace fse {
  namespace scene {
    namespace object {

      class FSE_API_EXPORT Material
      {
      public:
        Material();
        Material(Material &mat);
        ~Material();

        void            setColor(const float &r, const float &g, const float &b);
        void            setTexture(const std::string &file);
        void            setNormal(const std::string &file);
        void            setTexture(std::shared_ptr<gl_item::Texture> texture);
        void            setShader(std::shared_ptr<gl_item::Shader> shader);
        void            setRepeat(size_t repeat);

        std::shared_ptr<gl_item::Shader>     getShader();

        virtual void    useMaterial(std::shared_ptr<gl_item::Shader> shader = 0);

        Material        &operator=(Material &mat);

        protected:
            std::shared_ptr<gl_item::Texture> _texture;
          std::shared_ptr<gl_item::Texture> _normal;
          size_t                            _repeat;

          std::shared_ptr<gl_item::Shader>  _shader;

          glm::vec3                         _color;
      };

    } // object
  } // scene
} // fse

#endif
