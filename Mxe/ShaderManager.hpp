/**
 * @Author: daniel_b
 * @Date:   2017-08-22T21:40:12+02:00
 * @Last modified by:   daniel_b
 * @Last modified time: 2017-08-22T22:03:27+02:00
 */



#ifndef MXE_SHADER_MANAGER_HPP
#define MXE_SHADER_MANAGER_HPP

#include "Shader.hpp"

namespace mxe {

    class ShaderManager
    {
    public:
        ShaderManager();

        void        useDefaultProgram();
        void        useSpecialProgram(Shader *shader);

        Shader      *getActualShader();

    private:
        Shader      *_actual_shader;
        Shader      _default_shader;
        Shader      *_special_shader;
    };

}

#endif
