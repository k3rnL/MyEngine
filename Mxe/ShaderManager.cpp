/**
 * @Author: daniel_b
 * @Date:   2017-08-22T21:46:29+02:00
 * @Last modified by:   daniel_b
 * @Last modified time: 2017-09-18T14:30:45+02:00
 */



#include "Mxe/ShaderManager.hpp"

using namespace mxe;

ShaderManager::ShaderManager()
{
    _actual_shader = 0;
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

    return (0);
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
