/**
 * @Author: daniel_b
 * @Date:   2017-07-31T04:18:19+02:00
 * @Last modified by:   daniel_b
 * @Last modified time: 2017-09-07T01:11:06+02:00
 */



#ifndef INODE_HPP
#define INODE_HPP

#include <list>

#include <glm/glm.hpp>

#include "Mxe/ShaderManager.hpp"
#include "Mxe/Renderer/ObjectsToDrawCallback.hpp"

extern unsigned int g_count;

namespace mxe {
    namespace scene {

        class INode
        {
        public:
            INode();
            virtual ~INode() {}

            virtual INode   *clone();
            virtual void    draw(renderer::ObjectsToDrawCallback &callback,
                                 const glm::mat4 &transform);

            virtual void          setPosition(const glm::vec3 &position);
            virtual void          setRotation(const glm::vec3 &rotation);
            virtual void          setScale(const glm::vec3 &scale);

            virtual glm::vec3     &getPosition();
            virtual glm::vec3     &getRotation();
            virtual glm::vec3     &getScale();

            virtual void          addChild(INode *child);

        protected:

          glm::vec3       _position;
          glm::vec3       _rotation;
          glm::vec3       _scale;

          unsigned int        reference_count = 0;
          std::list<INode *>  childs;
        };

    }
}

#endif
