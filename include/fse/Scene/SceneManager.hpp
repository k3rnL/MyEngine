/**
 * @Author: daniel_b
 * @Date:   2017-07-31T04:39:05+02:00
 * @Last modified by:
 * @Last modified time: 2018-02-05T02:57:54+01:00
 */



#ifndef SCENEMANAGER_HPP
#define SCENEMANAGER_HPP

#include <map>
#include <vector>
#include <string>

#include "fse/Scene/INode.hpp"
#include "fse/Scene/ICamera.hpp"
#include "fse/Scene/Light.hpp"
#include "fse/Scene/Object/Object.hpp"
#include "fse/Scene/Object/Wavefront.hpp"

namespace fse {
    namespace scene {

        class FSE_API_EXPORT SceneManager
        {
        public:
            SceneManager();
            ~SceneManager();

            void                  addChild(INode *node);

            object::Object        *addWavefront(std::string const &file);
            object::Object        *createWavefront(std::string const &file);

            std::vector<INode *>  &getNodes();
            std::shared_ptr<Light>  getLight();
            void                    setLight(std::shared_ptr<Light>);

            object::Object      *launchRay(int x, int y, glm::mat4 &projection);

            ICamera                           *camera;

        private:
            std::map<std::string, INode *>      nodes_data;
            std::vector<INode *>                nodes;
            std::shared_ptr<Light>              light;
        };

    }
}

#endif
