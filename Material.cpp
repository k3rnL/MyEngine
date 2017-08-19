/**
 * @Author: daniel_b
 * @Date:   2017-07-25T02:33:19+02:00
 * @Last modified by:   daniel_b
 * @Last modified time: 2017-08-19T18:25:39+02:00
 */

#include "Material.hpp"
#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#endif
#include <Extra/stb_image.h>


using namespace mxe::scene::object;

Shader *Material::_shader = 0;

Material::Material()
{
  if (!_shader)
    _shader = new Shader("shader/basic_light.vert", "shader/basic_light.frag");
}

void        Material::setTexture(const std::string &file)
{
    glUseProgram(_shader->getProgram());

    glGenTextures(1, &_texture_id);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, _texture_id);

    int x, y, n;
    unsigned char   *data = stbi_load(file.c_str(), &x, &y, &n, 0);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, x, y, 0, GL_BGR, GL_UNSIGNED_BYTE, data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    glGenerateMipmap(GL_TEXTURE_2D);
    // applyMaterial();
}

void      Material::applyMaterial()
{
  glUseProgram(_shader->getProgram());
  _shader->setUniformValue(_color, "mt_data.diffuse_color");

  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, _texture_id);
  _shader->setUniformValue(0, "diffuse_map");

  _shader->setUniformValue(_texture_id ? 1 : 0, "mt_data.diffuse_map");
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
