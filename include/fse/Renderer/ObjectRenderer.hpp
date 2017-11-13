/**
 * @Author: daniel_b
 * @Date:   2017-08-29T23:40:59+02:00
 * @Last modified by:   daniel_b
 * @Last modified time: 2017-11-13T00:44:23+01:00
 */



#ifndef MXE_OBJECT_RENDERER_HPP
#define MXE_OBJECT_RENDERER_HPP

#include <list>
#include <map>
#include <utility>

#include "fse/GLItem/Mesh.hpp"
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

        private:
            // const glm::mat4     &_projection;
            ObjectsToDrawCallback   _callback;

            // std::map<std::shared_ptr<scene::object::Material>,
            //
            //          std::list< std::pair<std::shared_ptr<gl_item::Mesh>,
            //                               std::list<glm::mat4>
            //                              >
            //                   >
            //         > objects;
        };

    }
}

#endif
