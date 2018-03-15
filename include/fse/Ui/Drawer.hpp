/**
 * @Date:   2018-03-13T00:21:28+01:00
 * @Last modified time: 2018-03-13T00:22:07+01:00
 */

#ifndef FSE_UI_DRAWER_HPP
#define FSE_UI_DRAWER_HPP

#include <glm/glm.hpp>

#include "fse/GLItem/Shader.hpp"
#include "fse/GLItem/Mesh.hpp"

namespace fse {
    namespace ui {
        
		class FSE_API_EXPORT Drawer {
		public:
			Drawer(const glm::vec2 &size);

			void	drawRect(const glm::vec2 &pos, const glm::vec2 &size, const glm::vec4 &color);
			void	viewPort(const glm::vec2 &pos, const glm::vec2 &size);

			const glm::vec2		&getSize() { return size;  }

		private:
			std::shared_ptr<gl_item::Shader> 		shader;
			gl_item::Buffer<glm::vec3>				vertex_buffer;
			gl_item::Buffer<glm::vec2>				uv_buffer;
			std::vector<glm::vec3>					vertexes;
			glm::vec2								size;
		};

    } /* ui */
} /* fse */

#endif /* end of include guard: FSE_UI_DRAWER_HPP */
