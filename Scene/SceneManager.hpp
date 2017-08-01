/**
 * @Author: daniel_b
 * @Date:   2017-07-31T04:39:05+02:00
 * @Last modified by:   daniel_b
 * @Last modified time: 2017-08-01T00:43:22+02:00
 */



#ifndef SCENEMANAGER_HPP
#define SCENEMANAGER_HPP

#include <map>
#include <vector>
#include <string>

#include "Scene/INode.hpp"
#include "Scene/Object/Wavefront.hpp"

namespace mxe {
    namespace scene {

        class SceneManager
        {
        public:
            SceneManager();
            ~SceneManager();

            object::Wavefront    *addWavefront(std::string const &file);
            object::Wavefront    *createWavefront(std::string const &file);

        private:
            std::map<std::string, INode *>     nodes_data;
            std::vector<INode *>                nodes;
        };

    }
}

#endif
