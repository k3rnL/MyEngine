/**
 * @Author: daniel_b
 * @Date:   2017-07-25T02:33:19+02:00
 * @Last modified by:   daniel_b
 * @Last modified time: 2017-11-09T12:02:13+01:00
 */

#include "Material.hpp"
#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#endif
#include <Extra/stb_image.h>


using namespace mxe::scene::object;

Material::Material()
{
    _shader = ShaderManager::getInstance().getDefaultShader();
    _texture = 0;
}

Material::Material(Material &mat)
{
    _shader = mat._shader;
    _texture = mat._texture;
    _color = mat._color;
}

Material::~Material()
{
  if (_texture)
    {
      delete[] _texture->Texture_data;
      glDeleteBuffers(1, &_texture->Texture_id);
    }
}

void          Material::setTexture(const std::string &file)
{
  std::cout << "Load " << file << "\n";
  _texture = std::make_shared<Texture>();
  _texture->Name = file;

  ShaderManager::getInstance().useShader(_shader);

  glGenTextures(1, &_texture->Texture_id);
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, _texture->Texture_id);

  int x, y, n;
  unsigned char   *data = stbi_load(file.c_str(), &x, &y, &n, 0);

  glTexImage2D(GL_TEXTURE_2D, 0, GL_BGR, x, y, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 5); // pick mipmap level 7 or lower

  glGenerateMipmap(GL_TEXTURE_2D);
  glActiveTexture(GL_TEXTURE0);

  if (data)
    _texture->Texture_data = data;
}

void      Material::setShader(std::shared_ptr<Shader> shader) {
  _shader = shader;
}

void      Material::useMaterial()
{
  _shader->setUniformValue(_color, "mt_data.diffuse_color");

  if (_texture)
  {
    // glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, _texture->Texture_id);
    _shader->setUniformValue(0, "diffuse_map");
    _shader->setUniformValue(1, "mt_data.diffuse_map");

  }
  else
  {
    _shader->setUniformValue(0, "mt_data.diffuse_map");
  }

}

std::shared_ptr<Shader>    Material::getShader()
{
  return (_shader);
}

void      Material::setColor(const float &r, const float &g, const float &b)
{
  _color[0] = r;
  _color[1] = g;
  _color[2] = b;
}

Material  &Material::operator=(Material &mat)
{
  _texture = mat._texture;
  _color = mat._color;
  _shader = mat._shader;
  return (*this);
}
