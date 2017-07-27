/**
 * @Author: daniel_b
 * @Date:   2017-07-25T00:30:23+02:00
 * @Last modified by:   daniel_b
 * @Last modified time: 2017-07-25T14:13:54+02:00
 */



#ifndef WAVEFRONT_HPP
#define WAVEFRONT_HPP

#include <fstream>
#include <sstream>

#include "Object.hpp"

namespace mxe {
  namespace scene {
    namespace object {

      class Wavefront : public Object
      {
      public:
        Wavefront(const std::string &file);

        // virtual void  draw(Shader &shader, const glm::mat4 &view);
      };

    } // object
  } // scene
} // mxe

#endif
