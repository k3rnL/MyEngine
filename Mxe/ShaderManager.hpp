/**
 * @Author: daniel_b
 * @Date:   2017-08-22T21:40:12+02:00
 * @Last modified by:   daniel_b
 * @Last modified time: 2017-09-18T14:30:21+02:00
 */



#ifndef MXE_SHADER_MANAGER_HPP
#define MXE_SHADER_MANAGER_HPP

#include <memory>

#include "Shader.hpp"

namespace mxe {

    class ShaderManager
    {
    public:
        static  ShaderManager   &getInstance();

        std::shared_ptr<Shader>     addShader(const std::string &name);
        std::shared_ptr<Shader>     getActualShader();
        std::shared_ptr<Shader>     getDefaultShader();

        void                        destroyAll();

        void    setUniformValue(const glm::mat4 &matrix, const std::string &name);
        void    setUniformValue(const glm::vec3 &vec, const std::string &name);
        void    setUniformValue(const int value, const std::string &name);

    private:
        ShaderManager();
        static ShaderManager    _manager;

        struct                          ShaderInfo
        {
            std::string                 name;
            std::shared_ptr<Shader>     ptr;
        };

        std::vector<ShaderInfo>    _shaders;
        std::shared_ptr<Shader>    _actual_shader;
    };

}

#endif
