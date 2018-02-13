/**
 * @Author: daniel_b
 * @Date:   2017-08-22T21:40:12+02:00
 * @Last modified by:
 * @Last modified time: 2018-02-05T02:50:51+01:00
 */



#ifndef MXE_SHADER_MANAGER_HPP
#define MXE_SHADER_MANAGER_HPP

#include <memory>

#include "fse/Export.hpp"
#include "fse/GLItem/Shader.hpp"

namespace fse {

    class FSE_API_EXPORT ShaderManager
    {
    public:
        static  ShaderManager   &getInstance();

        std::shared_ptr<gl_item::Shader>     addShader(const std::string &name);
        std::shared_ptr<gl_item::Shader>     getActualShader();
        std::shared_ptr<gl_item::Shader>     getDefaultShader();
        void                        useShader(std::shared_ptr<gl_item::Shader> shader);

        void                        destroyAll();

        void    setUniformValue(const glm::mat4 &matrix, const std::string &name);
        void    setUniformValue(const glm::vec3 &vec, const std::string &name);
        void    setUniformValue(const int value, const std::string &name);
        void    setUniformValue(const float value, const std::string &name);

    private:
        ShaderManager();
        static ShaderManager    _manager;

        struct                          ShaderInfo
        {
            std::string                 name;
            std::shared_ptr<gl_item::Shader>     ptr;
        };

        std::vector<ShaderInfo>    _shaders;
        std::shared_ptr<gl_item::Shader>    _actual_shader;
    };

}

#endif
