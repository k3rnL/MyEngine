/**
 * @Author: daniel_b
 * @Date:   2017-08-22T21:46:29+02:00
 * @Last modified by:   daniel_b
 * @Last modified time: 2017-08-22T22:04:00+02:00
 */



#include "Mxe/ShaderManager.hpp"

using namespace mxe;

ShaderManager::ShaderManager() :
    _default_shader("shader/basic_light.vert", "shader/basic_light.frag")
{
    _special_shader = 0;
    _actual_shader = 0;
}

Shader  *ShaderManager::getActualShader()

{
    return (_actual_shader);
}

void    ShaderManager::useDefaultProgram()
{
    if (_actual_shader != &_default_shader)
    {
        glUseProgram(_default_shader.getProgram());
        _actual_shader = &_default_shader;
    }
}

void    ShaderManager::useSpecialProgram(Shader *shader)
{
    if (_actual_shader != shader)
    {
        glUseProgram(shader->getProgram());
        _actual_shader = shader;
    }
}
