/**
 * @Author: daniel_b
 * @Date:   2017-11-13T00:45:23+01:00
 * @Last modified by:
 * @Last modified time: 2018-02-05T02:51:08+01:00
 */



#ifndef WAVEFRONT_HPP
#define WAVEFRONT_HPP

#include <fstream>
#include <sstream>
#include <iostream>
#include <exception>

#include "fse/Export.hpp"
#include "fse/Scene/INode.hpp"
#include "fse/Scene/Object/Object.hpp"

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>

namespace fse {
  namespace scene {
    namespace object {


      class FSE_API_EXPORT Wavefront : public Object
      {
      public:
        Wavefront(const std::string &file);

        virtual void    draw(renderer::ObjectsToDrawCallback &callback,
                             const glm::mat4 &transform);

        static Object    *load(const std::string &file);
    private:
        Wavefront();
      };

    } // object
  } // scene
} // fse

#endif
