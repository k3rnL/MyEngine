/**
 * @Author: daniel_b
 * @Date:   2017-08-14T21:45:14+02:00
 * @Last modified by:
 * @Last modified time: 2018-02-05T02:50:30+01:00
 */



#ifndef ICAMERA_HPP
#define ICAMERA_HPP

#include "fse/Export.hpp"
#include "fse/Scene/INode.hpp"

namespace fse {
    namespace scene {

      class FSE_API_EXPORT ICamera : public INode
      {
      public:
        ICamera() { }
        virtual ~ICamera() { }

        virtual const glm::mat4   &getView() = 0;
        virtual const glm::vec3   &getDirection() = 0;

      };

    } // scene
} // fse

#endif
