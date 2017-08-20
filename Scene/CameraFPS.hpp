/**
 * @Author: daniel_b
 * @Date:   2017-08-16T16:18:48+02:00
 * @Last modified by:   daniel_b
 * @Last modified time: 2017-08-18T16:05:00+02:00
 */



#ifndef CAMERAFPS_HPP
#define CAMERAFPS_HPP

#include "Scene/ICamera.hpp"
#include <glm/gtx/transform.hpp>

namespace mxe {
    namespace scene {

      class CameraFPS : public ICamera
      {
      public:
        CameraFPS();
        virtual ~CameraFPS() { }

        void            mouseInput(const int x_relative, const int y_relative, const float deltaT);

        void            setMouseSpeed(float speed);
        void            setMoveSpeed(float speed);

        float           getMouseSpeed();
        float           getMoveSpeed();

        virtual const glm::mat4   &getView();
        virtual const glm::vec3   &getDirection();

        virtual INode             *clone();
        virtual void              setPosition(const glm::vec3 &position);

      private:
        glm::mat4       _view;
        glm::vec3       _direction;
        float           _vertical_angle;
        float           _horizontal_angle;
        float           _mouse_speed;
        float           _move_speed;
      };

    } // scene
} // mxe

#endif
