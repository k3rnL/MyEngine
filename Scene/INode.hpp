/**
 * @Author: daniel_b
 * @Date:   2017-07-31T04:18:19+02:00
 * @Last modified by:   daniel_b
 * @Last modified time: 2017-08-29T23:37:51+02:00
 */



#ifndef INODE_HPP
#define INODE_HPP

#include <list>

#include <glm/glm.hpp>

#include "Mxe/ShaderManager.hpp"

namespace mxe {
    namespace scene {

        class INode
        {
        public:
            INode() {}
            virtual ~INode() {}

            virtual INode   *clone() = 0;

            virtual void          setPosition(const glm::vec3 &position);
            virtual void          setRotation(const glm::vec3 &rotation);

            virtual glm::vec3     &getPosition();
            virtual glm::vec3     &getRotation();

        protected:

          glm::vec3       _position;
          glm::vec3       _rotation;

          unsigned int        reference_count = 0;
          std::list<INode *>  childs;
        };

    }
}

#endif
