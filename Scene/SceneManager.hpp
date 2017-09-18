/**
 * @Author: daniel_b
 * @Date:   2017-07-31T04:39:05+02:00
 * @Last modified by:   daniel_b
 * @Last modified time: 2017-09-12T23:06:43+02:00
 */



#ifndef SCENEMANAGER_HPP
#define SCENEMANAGER_HPP

#include <map>
#include <vector>
#include <string>

#include "Scene/INode.hpp"
#include "Object.hpp"
#include "Scene/ICamera.hpp"
#include "Scene/Object/Wavefront.hpp"

namespace mxe {
    namespace scene {

        class SceneManager
        {
        public:
            SceneManager();
            ~SceneManager();

            void                addChild(INode *node);

            object::Object    *addWavefront(std::string const &file);
            object::Object    *createWavefront(std::string const &file);

            std::vector<INode *> &getNodes();

            ICamera                           *camera;

        private:
            std::map<std::string, INode *>     nodes_data;
            std::vector<INode *>      nodes;

        };

    }
}

#endif
