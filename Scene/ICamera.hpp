/**
 * @Author: daniel_b
 * @Date:   2017-08-14T21:45:14+02:00
 * @Last modified by:   daniel_b
 * @Last modified time: 2017-08-18T15:35:31+02:00
 */



#ifndef ICAMERA_HPP
#define ICAMERA_HPP

#include "Scene/INode.hpp"

namespace mxe {
    namespace scene {

      class ICamera : public INode
      {
      public:
        ICamera() { }
        virtual ~ICamera() { }

        virtual const glm::mat4   &getView() = 0;
        virtual const glm::vec3   &getDirection() = 0;

      };

    } // scene
} // mxe

#endif
