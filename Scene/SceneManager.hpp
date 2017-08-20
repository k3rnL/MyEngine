/**
 * @Author: daniel_b
 * @Date:   2017-07-31T04:39:05+02:00
 * @Last modified by:   daniel_b
 * @Last modified time: 2017-08-16T17:05:10+02:00
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

            object::Wavefront    *addWavefront(std::string const &file);
            object::Wavefront    *createWavefront(std::string const &file);

            ICamera                           *camera;

            const std::vector<object::Object *>        &getDrawable();

        private:
            std::map<std::string, INode *>     nodes_data;
            std::vector<object::Object *>                nodes;

        };

    }
}

#endif
