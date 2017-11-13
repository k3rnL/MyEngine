/**
 * @Author: daniel_b
 * @Date:   2017-07-31T23:52:43+02:00
 * @Last modified by:   daniel_b
 * @Last modified time: 2017-11-13T00:47:16+01:00
 */



#include "fse/Scene/SceneManager.hpp"

using namespace fse::scene;

SceneManager::SceneManager()
{

}

SceneManager::~SceneManager()
{

}

fse::scene::object::Object          *SceneManager::addWavefront(const std::string &file)
{
    object::Object                  *obj;

    if (nodes_data.find(file) != nodes_data.end())
        obj = (object::Wavefront *) nodes_data.find(file)->second->clone();
    else
    {
      obj = createWavefront(file);
      std::cout << "Create a new " << file << "\n";
    }
    nodes.push_back(obj);
    return (obj);
}

fse::scene::object::Object           *SceneManager::createWavefront(const std::string &file)
{
    object::Object                   *obj;

    obj = object::Wavefront::load(file);
    nodes_data[file] = obj;
    nodes.push_back(obj);
    return (obj);
}

void                        SceneManager::addChild(INode *node)
{
    nodes.push_back(node);
}

std::vector<INode *>        &SceneManager::getNodes()
{
    return (nodes);
}

glm::vec3                   &SceneManager::getLight() {
  return (light);
}
