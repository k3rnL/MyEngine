/**
 * @Author: daniel_b
 * @Date:   2017-07-31T04:39:05+02:00
 * @Last modified by:   daniel_b
 * @Last modified time: 2017-11-13T00:46:01+01:00
 */



#ifndef SCENEMANAGER_HPP
#define SCENEMANAGER_HPP

#include <map>
#include <vector>
#include <string>

#include "fse/Scene/INode.hpp"
#include "fse/Scene/ICamera.hpp"
#include "fse/Scene/Object/Object.hpp"
#include "fse/Scene/Object/Wavefront.hpp"

namespace fse {
    namespace scene {

        class SceneManager
        {
        public:
            SceneManager();
            ~SceneManager();

            void                  addChild(INode *node);

            object::Object        *addWavefront(std::string const &file);
            object::Object        *createWavefront(std::string const &file);

            std::vector<INode *>  &getNodes();
            glm::vec3             &getLight();

            ICamera                           *camera;

        private:
            std::map<std::string, INode *>      nodes_data;
            std::vector<INode *>                nodes;
            glm::vec3                           light;
        };

    }
}

#endif
