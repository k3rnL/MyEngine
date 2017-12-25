/**
 * @Author: daniel_b
 * @Date:   2017-07-25T02:33:19+02:00
 * @Last modified by:   daniel_b
 * @Last modified time: 2017-11-19T20:34:52+01:00
 */

#include "fse/Material.hpp"

using namespace fse::scene::object;
using namespace fse::gl_item;

Material::Material()
{
    _shader = ShaderManager::getInstance().getDefaultShader();
    _texture = 0;
    _normal = 0;
    _repeat = 1;
}

Material::Material(Material &mat)
{
    _shader = mat._shader;
    _texture = mat._texture;
    _color = mat._color;
}

Material::~Material()
{
}

void          Material::setTexture(const std::string &file)
{
    _texture = gl_item::Texture::load(file);
}

void          Material::setTexture(std::shared_ptr<gl_item::Texture> texture) {
    _texture = texture;
}

void          Material::setNormal(const std::string &file) {
    _normal = gl_item::Texture::load(file);
    _normal->setMipMapLevel(0);
}

void        Material::setRepeat(size_t repeat) {
    _repeat = repeat;
}

void      Material::setShader(std::shared_ptr<Shader> shader) {
  _shader = shader;
}

void      Material::useMaterial()
{
    _shader->setUniformValue(_color, "mt_data.diffuse_color");
    _shader->setUniformValue((int)_repeat, "mt_data.repeat");

  if (_texture)
  {
      _texture->activate(0);
      _texture->bind();
      _shader->setUniformValue(0, "diffuse_map");
      _shader->setUniformValue(1, "mt_data.diffuse_map");

  }
  else
  {
    _shader->setUniformValue(0, "mt_data.diffuse_map");
  }

  if (_normal)
  {
      _normal->activate(1);
      _normal->bind();
      _shader->setUniformValue(1, "normal_map");
      _shader->setUniformValue(1, "mt_data.normal_map");
  }
  else
    _shader->setUniformValue(0, "mt_data.normal_map");
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
