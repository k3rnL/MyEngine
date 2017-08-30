/**
 * @Author: daniel_b
 * @Date:   2017-07-31T23:52:43+02:00
 * @Last modified by:   daniel_b
 * @Last modified time: 2017-08-30T04:46:50+02:00
 */



#include "Scene/SceneManager.hpp"

using namespace mxe::scene;

SceneManager::SceneManager()
{

}

SceneManager::~SceneManager()
{

}

object::Wavefront           *SceneManager::addWavefront(const std::string &file)
{
    object::Wavefront       *obj;

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

object::Wavefront           *SceneManager::createWavefront(const std::string &file)
{
    object::Wavefront       *obj;

    obj = new object::Wavefront(file);
    nodes_data[file] = obj;
    nodes.push_back(obj);
    _instancied_mesh.push_back(obj->getMesh());
    return (obj);
}

const std::vector<std::shared_ptr<mxe::gl_item::Mesh>>   &SceneManager::getDrawable()
{
  return (_instancied_mesh);
}

const std::vector<object::Object *>       &SceneManager::getObjects()
{
    return (nodes);
}
