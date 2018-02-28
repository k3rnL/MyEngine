/**
 * @Author: daniel_b
 * @Date:   2017-08-16T16:18:48+02:00
 * @Last modified by:
 * @Last modified time: 2018-02-05T02:58:58+01:00
 */



#ifndef CAMERAFPS_HPP
#define CAMERAFPS_HPP

#include <cmath>

#include "glm/gtc/matrix_transform.hpp"

#include "fse/Scene/ICamera.hpp"

namespace fse {
    namespace scene {

      class FSE_API_EXPORT CameraFPS : public ICamera
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
} // fse

#endif
