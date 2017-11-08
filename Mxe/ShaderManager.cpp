/**
 * @Author: daniel_b
 * @Date:   2017-08-22T21:46:29+02:00
 * @Last modified by:   daniel_b
 * @Last modified time: 2017-11-08T18:20:31+01:00
 */



#include "Mxe/ShaderManager.hpp"

using namespace mxe;

ShaderManager   ShaderManager::_manager = ShaderManager();

ShaderManager::ShaderManager()
{
    _actual_shader = 0;
}

void            ShaderManager::useShader(std::shared_ptr<Shader> shader)
{
    if (_actual_shader != shader)
    {
        shader->useProgram();
        _actual_shader = shader;
    }
}

ShaderManager   &ShaderManager::getInstance() {
    return (_manager);
}

std::shared_ptr<Shader>     ShaderManager::getActualShader() {
    return (_actual_shader);
}

std::shared_ptr<Shader>     ShaderManager::getDefaultShader() {
    if (_shaders.size())
        return (_shaders[0].ptr);
    else
        return (0);
}

std::shared_ptr<Shader>     ShaderManager::addShader(const std::string &name)
{
    for (auto shader : _shaders)
    {
        if (shader.name == name)
            return (shader.ptr);
    }

    std::shared_ptr<Shader>   shader = std::make_shared<Shader>("shader/" + name + ".vert",
                                                                "shader/" + name + ".frag");
    _shaders.push_back({name, shader});
    if (_shaders.size() == 1)
      useShader(shader);
    return (shader);
}

void    ShaderManager::destroyAll() {
    _shaders.clear();
}

void    ShaderManager::setUniformValue(const glm::mat4 &matrix, const std::string &name)
{
    for (auto shader : _shaders) {
        shader.ptr->setUniformValue(matrix, name);
    }
}

void    ShaderManager::setUniformValue(const glm::vec3 &vec, const std::string &name)
{
    for (auto shader : _shaders) {
        shader.ptr->setUniformValue(vec, name);
    }
}

void    ShaderManager::setUniformValue(const int value, const std::string &name)
{
    for (auto shader : _shaders) {
        shader.ptr->setUniformValue(value, name);
    }
}

void    ShaderManager::setUniformValue(const float value, const std::string &name)
{
    for (auto shader : _shaders) {
        shader.ptr->setUniformValue(value, name);
    }
}
