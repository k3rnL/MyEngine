/**
 * @Author: daniel_b
 * @Date:   2017-07-25T02:33:19+02:00
 * @Last modified by:   daniel_b
 * @Last modified time: 2017-07-30T23:57:32+02:00
 */

#include "Material.hpp"

using namespace mxe::scene::object;

Material::Material()
{
  _shader = new Shader("shader/basic_light.vert", "shader/basic_light.frag");
}

void      Material::applyMaterial()
{
  glUseProgram(_shader->getProgram());
  GLuint  attr_id = glGetUniformLocation(_shader->getProgram(), "mat_color");
  glUniform3fv(attr_id, 1, &_color[0]);
}

Shader    &Material::getShader()
{
  return (*_shader);
}

void      Material::setColor(const float &r, const float &g, const float &b)
{
  _color[0] = r;
  _color[1] = g;
  _color[2] = b;
}
