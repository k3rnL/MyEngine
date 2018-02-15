/**
 * @Author: daniel_b
 * @Date:   2017-07-31T04:39:05+02:00
 * @Last modified by:
 * @Last modified time: 2018-02-14T23:15:54+01:00
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
            virtual ~SceneManager();

            void                  addChild(INode *node);

            virtual object::Object        *addObject(std::string const &file);
            virtual object::Object        *createObject(std::string const &file);

            std::vector<INode *>    &getNodes();
            std::shared_ptr<Light>  getLight();
            void                    setLight(std::shared_ptr<Light>);

            object::Object      *launchRay(int x, int y, glm::mat4 &projection);

            ICamera                           *camera;

        protected:
            std::map<std::string, std::shared_ptr<gl_item::Mesh> >	mesh_catalog;
            std::vector<INode *>									nodes;
            std::shared_ptr<Light>									light;
        };

    }
}

#endif
