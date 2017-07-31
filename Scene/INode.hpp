/**
 * @Author: daniel_b
 * @Date:   2017-07-31T04:18:19+02:00
 * @Last modified by:   daniel_b
 * @Last modified time: 2017-07-31T04:35:35+02:00
 */



#ifndef INODE_HPP
#define INODE_HPP

namespace mxe {
    namespace scene {

        class INode
        {
        public:
            INode() {}
            virtual ~INode() {}

            virtual INode   *clone() = 0;
        };

    }
}

#endif
