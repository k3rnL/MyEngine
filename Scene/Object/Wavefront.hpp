/**
 * @Author: daniel_b
 * @Date:   2017-07-25T00:30:23+02:00
 * @Last modified by:   daniel_b
 * @Last modified time: 2017-09-06T23:41:48+02:00
 */



#ifndef WAVEFRONT_HPP
#define WAVEFRONT_HPP

#include <fstream>
#include <sstream>
#include <iostream>
#include <exception>

#include "Object.hpp"
#include "Scene/INode.hpp"

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>

namespace mxe {
  namespace scene {
    namespace object {


      class Wavefront : public Object
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
} // mxe

#endif
