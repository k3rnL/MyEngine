/**
 * @Author: daniel_b
 * @Date:   2017-07-25T02:33:19+02:00
 * @Last modified by:   daniel_b
 * @Last modified time: 2017-08-01T14:07:20+02:00
 */

#include "Material.hpp"
#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#endif
#include <Extra/stb_image.h>


using namespace mxe::scene::object;

Material::Material()
{
  _shader = new Shader("shader/basic_light.vert", "shader/basic_light.frag");
}

void        Material::setTexture(const std::string &file)
{
    glUseProgram(_shader->getProgram());

    glGenTextures(1, &_texture_id);
    glBindTexture(GL_TEXTURE_2D, _texture_id);

    int x, y, n;
    unsigned char   *data = stbi_load(file.c_str(), &x, &y, &n, 0);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, x, y, 0, GL_BGR, GL_UNSIGNED_BYTE, data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

}

void      Material::applyMaterial()
{
  glUseProgram(_shader->getProgram());
  GLuint  attr_id = glGetUniformLocation(_shader->getProgram(), "mat_color");
  glUniform3fv(attr_id, 1, &_color[0]);

  attr_id = glGetUniformLocation(_shader->getProgram(), "diffuse_map");
  glUniform1i(attr_id, _texture_id);
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
