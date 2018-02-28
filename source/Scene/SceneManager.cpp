/**
 * @Author: daniel_b
 * @Date:   2017-07-31T23:52:43+02:00
 * @Last modified by:   daniel_b
 * @Last modified time: 2017-11-21T02:48:02+01:00
 */



#include "fse/Scene/SceneManager.hpp"

using namespace fse::scene;

SceneManager::SceneManager()
{
}

SceneManager::~SceneManager()
{

}

fse::scene::object::Object          *SceneManager::addObject(const std::string &file)
{
    object::Object                  *obj;

    if (mesh_catalog.find(file) != mesh_catalog.end())
        obj = new object::Object(mesh_catalog.find(file)->second);
    else
		obj = createObject(file);
    nodes.push_back(obj);
    return (obj);
}

fse::scene::object::Object           *SceneManager::createObject(const std::string &file)
{
    object::Object                   *obj;

    obj = object::Wavefront::load(file);
	mesh_catalog[file] = obj->getMesh();
    return (obj);
}

struct ray_result
{
    object::Object *obj;
    float           distance;
};

bool intersect(float &result, const glm::vec3 &orig, const glm::vec3 &dir, const glm::vec3 &min, const glm::vec3 &max)
{
    glm::vec3 dirfrac;
    float t;
    dirfrac.x = 1.0f / dir.x;
    dirfrac.y = 1.0f / dir.y;
    dirfrac.z = 1.0f / dir.z;
    // lb is the corner of AABB with minimal coordinates - left bottom, rt is maximal corner
    // r.org is origin of ray
    float t1 = (min.x - orig.x)*dirfrac.x;
    float t2 = (max.x - orig.x)*dirfrac.x;
    float t3 = (min.y - orig.y)*dirfrac.y;
    float t4 = (max.y - orig.y)*dirfrac.y;
    float t5 = (min.z - orig.z)*dirfrac.z;
    float t6 = (max.z - orig.z)*dirfrac.z;

    float tmin = std::max(std::max(std::min(t1, t2), std::min(t3, t4)), std::min(t5, t6));
    float tmax = std::min(std::min(std::max(t1, t2), std::max(t3, t4)), std::max(t5, t6));

    // if tmax < 0, ray (line) is intersecting AABB, but the whole AABB is behind us
    if (tmax < 0)
    {
        t = tmax;
        return false;
    }

    // if tmin > tmax, ray doesn't intersect AABB
    if (tmin > tmax)
    {
        t = tmax;
        return false;
    }

    if (tmin < 0)
        return false;
    result = tmin;
    return true;
}
ray_result  *ray_recurs(INode *node, glm::vec3 &orig, glm::vec3 &dir) {
    ray_result *result_data = 0;
        object::Object *obj = (object::Object*) node;
        obj->getMesh();
        float result;

        if (intersect(result, orig - obj->getPosition(), dir, obj->getMesh()->_min, obj->getMesh()->_max)) {
            // float distance = glm::distance(orig, result);
            std::cout << "Result:" << result << "\n";
            std::cout << "x: " << orig.x << " y: " << orig.y << "z: " << orig.z << "\n";
            if (result > 0) {
                if (result_data)
                    delete result_data;
                result_data = new ray_result;
                result_data->obj = obj;
                result_data->distance = result;
            }
        }

        for (auto sub_node : node->getChilds()) {
            ray_result *recurs = ray_recurs(sub_node, orig, dir);
            if (recurs) {
                if (result_data == 0)
                    result_data = recurs;
                else if (recurs->distance < result_data->distance) {
                    delete result_data;
                    result_data = recurs;
                }
            }
        }

    return result_data;
}

object::Object              *SceneManager::launchRay(int x_screen, int y_screen, glm::mat4 &proj)
{
    float x = (2.0f * x_screen) / 1540.0f - 1.0f;
    float y = 1.0f - (2.0f * y_screen) / 1024;
    // glm::vec4 ray_clip(x, y, -1, 1);
    glm::vec4 ray_clip(1, 1, -1, 1);
    glm::vec4 ray_eye = glm::inverse(proj) * ray_clip;
    ray_eye = glm::vec4(ray_eye.x, ray_eye.y, -1, 0);
    glm::vec3 ray = glm::vec3(glm::inverse(camera->getView()) * ray_eye);
    ray = glm::normalize(ray);
    // ray = glm::vec3(0,-1,0);
    ray_result *result_data = 0;

    // float r;
    // bool b = intersect(r, camera->getPosition(), ray, glm::vec3(-100, -1, -100), glm::vec3(100, 1, 100));
    // std::cout << "Result b" << b << " " << r << "\n";
    for (auto node : nodes) {
        ray_result *recurs = ray_recurs(node, camera->getPosition(), ray);
        if (recurs) {
            if (!result_data)
                result_data = recurs;
            else if (recurs->distance < result_data->distance) {
                delete result_data;
                result_data = recurs;
            }
        }
    }
    if (result_data){
        std::cout << "rsult=" << result_data->distance << "\n";
        std::cout << "min: x=" << result_data->obj->getMesh()->_min.x << "\n";
        std::cout << "min: y=" << result_data->obj->getMesh()->_min.y << "\n";
        std::cout << "min: z=" << result_data->obj->getMesh()->_min.z << "\n";
        std::cout << "max: x=" << result_data->obj->getMesh()->_max.x << "\n";
        std::cout << "max: y=" << result_data->obj->getMesh()->_max.y << "\n";
        std::cout << "max: z=" << result_data->obj->getMesh()->_max.z << "\n";
        result_data->obj->getPosition() += glm::vec3(0,1,0);
    }
    delete result_data;
	return (0);
}

void                        SceneManager::addChild(INode *node)
{
    nodes.push_back(node);
}

std::vector<INode *>        &SceneManager::getNodes()
{
    return (nodes);
}

std::shared_ptr<Light>      SceneManager::getLight() {
  return (light);
}

void                    SceneManager::setLight(std::shared_ptr<Light> light) {
    this->light = light;
}
