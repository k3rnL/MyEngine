/**
 * @Author: daniel_b
 * @Date:   2017-08-16T16:25:47+02:00
 * @Last modified by:   daniel_b
 * @Last modified time: 2017-11-14T22:18:11+01:00
 */



#include "fse/Scene/CameraFPS.hpp"

using namespace fse::scene;

CameraFPS::CameraFPS()
{
  _horizontal_angle = M_PI;
  _vertical_angle = 0;

  _mouse_speed = 0.20;
  _move_speed = 4;

  mouseInput(0, 0, 0);
}

void          CameraFPS::mouseInput(const int x_relative, const int y_relative, const float deltaT)
{
  _horizontal_angle -= _mouse_speed * x_relative * deltaT;
  _vertical_angle -= _mouse_speed * y_relative * deltaT;

  _vertical_angle = glm::clamp((double) _vertical_angle, -M_PI / 2., M_PI + M_PI / 2);

  _direction = glm::vec3(cos(_vertical_angle) * sin(_horizontal_angle),
                        sin(_vertical_angle),
                        cos(_vertical_angle) * cos(_horizontal_angle));

  _direction = glm::normalize(_direction);

  glm::vec3 right = glm::vec3(sin(_horizontal_angle - 3.14f/2.0f),
                              0,
                              cos(_horizontal_angle - 3.14f/2.0f));

  glm::vec3 up = glm::cross(right, _direction);
  _view = glm::lookAt(_position, _position + _direction, up);
}

const glm::mat4       &CameraFPS::getView() {
    // _view = glm::lookAt(getPosition(), getPosition() + glm::vec3(0,-1,0), glm::vec3(0,0,1));

  return (_view);
}

const glm::vec3       &CameraFPS::getDirection()
{
  return (_direction);
}

void                  CameraFPS::setPosition(const glm::vec3 &position) {
  INode::setPosition(position);
  mouseInput(0, 0, 0);
}

INode                 *CameraFPS::clone()
{
  CameraFPS           *cam = new CameraFPS();

  cam->_view = _view;
  cam->_direction = _direction;
  cam->_horizontal_angle = _horizontal_angle;
  cam->_vertical_angle = _vertical_angle;
  cam->_mouse_speed = _mouse_speed;
  cam->_move_speed = _move_speed;
  return (cam);
}
