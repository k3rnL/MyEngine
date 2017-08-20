/**
 * @Author: daniel_b
 * @Date:   2017-07-25T02:33:19+02:00
 * @Last modified by:   daniel_b
 * @Last modified time: 2017-08-03T22:14:28+02:00
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

  GLuint block_id = glGetUniformBlockIndex(_shader->getProgram(), "mt_data");
  glUniformBlockBinding(_shader->getProgram(), block_id, 0); // 0 is binding point id

  glGenBuffers(1, &_mt_data_buffer_id);
  glBindBuffer(GL_UNIFORM_BUFFER, _mt_data_buffer_id);

  glBufferData(GL_UNIFORM_BUFFER, sizeof (MaterialData), &_data, GL_STATIC_DRAW);
  glBindBufferBase(GL_UNIFORM_BUFFER, 0, _mt_data_buffer_id); // 0 is binding point id
}

void        Material::setTexture(const std::string &file)
{
    glUseProgram(_shader->getProgram());

    glGenTextures(1, &_texture_id);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, _texture_id);

    int x, y, n;
    unsigned char   *data = stbi_load(file.c_str(), &x, &y, &n, 0);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, x, y, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    GLuint attr_id = glGetUniformLocation(_shader->getProgram(), "diffuse_map");
    glUniform1i(attr_id, 0);
    glGenerateMipmap(GL_TEXTURE_2D);
    // applyMaterial();
}

void      Material::applyMaterial()
{
  glUseProgram(_shader->getProgram());
  GLuint  attr_id = glGetUniformLocation(_shader->getProgram(), "mat_color");
  glUniform3fv(attr_id, 1, &_color[0]);

  if (_texture_id)
    _data.diffuse_map = 1;
  else
    _data.diffuse_map = 0;
  memcpy(&_data.diffuse_color, &_color[0], sizeof (float) * 3);

  glBindBuffer(GL_UNIFORM_BUFFER, _mt_data_buffer_id);
  glBufferData(GL_UNIFORM_BUFFER, sizeof (MaterialData), &_data, GL_DYNAMIC_DRAW);
  glBindBufferBase(GL_UNIFORM_BUFFER, 0, _mt_data_buffer_id); // 0 is binding point id
  
  // attr_id = glGetUniformLocation(_shader->getProgram(), "diffuse_map");
  // glUniform1i(attr_id, 0);
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
