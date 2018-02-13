/**
 * @Author: daniel_b
 * @Date:   2017-09-06T01:26:02+02:00
 * @Last modified by:
 * @Last modified time: 2018-02-05T02:51:35+01:00
 */



#ifndef MXE_OBJECT_TO_DRAW_HPP
#define MXE_OBJECT_TO_DRAW_HPP

#include <memory>
#include <map>
#include <list>

#include "fse/Export.hpp"
#include "fse/Material.hpp"
#include "fse/GLItem/Mesh.hpp"

namespace fse {
    namespace renderer {

        class FSE_API_EXPORT ObjectsToDrawCallback
        {
            friend class ObjectRenderer;

        public:
            void        addObject(std::shared_ptr<scene::object::Material>  mat,
                                  std::shared_ptr<gl_item::Mesh>            mesh,
                                  const glm::mat4                           &transform);

        private:

            std::map<
              std::shared_ptr<gl_item::Shader>,
              std::map<
                std::shared_ptr<scene::object::Material>,
                std::map<
                  std::shared_ptr<gl_item::Mesh>,
                  std::list<glm::mat4>
                >
              >
            > objects;

        };

    }
}

#endif
