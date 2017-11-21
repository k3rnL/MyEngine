/**
 * @Author: daniel_b
 * @Date:   2017-08-29T23:40:59+02:00
 * @Last modified by:   daniel_b
 * @Last modified time: 2017-11-20T22:13:10+01:00
 */



#ifndef MXE_OBJECT_RENDERER_HPP
#define MXE_OBJECT_RENDERER_HPP

#include <list>
#include <map>
#include <utility>

#include "fse/GLItem/Mesh.hpp"
#include "fse/GLItem/Texture.hpp"
#include "fse/Material.hpp"
#include "fse/Scene/INode.hpp"
#include "fse/ShaderManager.hpp"
#include "fse/Renderer/ObjectsToDrawCallback.hpp"

namespace fse {
    namespace renderer {

        class ObjectRenderer
        {
        public:
            // ObjectRenderer(const glm::mat4 &projection);
            ObjectRenderer();

            // void    addObject(std::shared_ptr<scene::object::Material> mat, std::shared_ptr<gl_item::Mesh> mesh, const glm::mat4 &transform);
            void    clean();

            void    addNode(scene::INode *node);

            void    drawAll();
            void    drawAll(std::shared_ptr<gl_item::Shader> shader);

            void    setShadowMap(std::shared_ptr<gl_item::Texture> texture);

        private:
            std::shared_ptr<gl_item::Texture>   _shadow;
            ObjectsToDrawCallback   _callback;
            std::shared_ptr<fse::gl_item::Texture>       _depth;
        };

    }
}

#endif
