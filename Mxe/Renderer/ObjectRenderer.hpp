/**
 * @Author: daniel_b
 * @Date:   2017-08-29T23:40:59+02:00
 * @Last modified by:   daniel_b
 * @Last modified time: 2017-08-30T04:57:52+02:00
 */



#ifndef MXE_OBJECT_RENDERER_HPP
#define MXE_OBJECT_RENDERER_HPP

#include <list>
#include <map>
#include <utility>

#include "GLItem/Mesh.hpp"
#include "Material.hpp"
#include "Mxe/ShaderManager.hpp"

namespace mxe {
    namespace renderer {

        class ObjectRenderer
        {
        public:
            ObjectRenderer(const glm::mat4 &projection);

            void    addObject(std::shared_ptr<scene::object::Material> mat, std::shared_ptr<gl_item::Mesh> mesh, const glm::mat4 &transform);
            void    clean();

            void    drawAll(ShaderManager &shaders);

        private:
            const glm::mat4     &_projection;

            std::map<std::shared_ptr<scene::object::Material>,

                     std::list< std::pair<std::shared_ptr<gl_item::Mesh>,
                                          std::list<glm::mat4>
                                         >
                              >
                    > objects;
        };

    }
}

#endif
