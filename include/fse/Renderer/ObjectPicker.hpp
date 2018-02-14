/**
 * @Date:   2018-02-14T03:55:52+01:00
 * @Last modified time: 2018-02-14T06:53:24+01:00
 */

#ifndef FSE_OBJECT_PICKER_HPP
#define FSE_OBJECT_PICKER_HPP

#include "fse/Renderer/ObjectRenderer.hpp"

namespace fse {
    namespace renderer {

        class FSE_API_EXPORT ObjectPicker : public ObjectRenderer
        {
        public:
            ObjectPicker(unsigned int width, unsigned int height);
            ~ObjectPicker();
            scene::object::Object   *pickObject(const glm::mat4 &projection, const glm::mat4 &view, int x, int y);

        private:
            virtual void onDrawBegin();
            virtual void onPreDrawItem(std::shared_ptr<gl_item::Shader> shader, std::shared_ptr<fse::scene::object::Material> material, std::shared_ptr<gl_item::Mesh> mesh, scene::object::Object *object, glm::mat4 const &transform);
            virtual void onDrawFinished();

            GLuint          frame_buffer;
            std::map<unsigned int, scene::object::Object *> objects;
            unsigned int    id;
			unsigned int    id_found;

            std::shared_ptr<gl_item::Shader>    shader;
            unsigned int width;
            unsigned int height;
        };

    }
}

#endif /* end of include guard: FSE_OBJECT_PICKER_HPP */
