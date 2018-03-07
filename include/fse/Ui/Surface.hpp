/**
 * @Date:   2018-02-23T00:46:33+01:00
 * @Last modified time: 2018-02-23T01:04:03+01:00
 */
#ifndef FSE_UI_SURFACE_HPP
#define FSE_UI_SURFACE_HPP

#include <glm/glm.hpp>

#include <list>

#include "fse/Export.hpp"
#include "fse/GLItem/Texture.hpp"
#include "fse/GLItem/Shader.hpp"
#include "fse/GLItem/Mesh.hpp"

namespace fse {
    namespace ui {

        class FSE_API_EXPORT Surface {
        public:
			Surface();
			virtual ~Surface() {}

			virtual void	setSize(const glm::vec2 &size);
			virtual void	setMaximumSize(const glm::vec2 &max);
			virtual void	setPos(const glm::vec2 &pos);
            virtual void    setBackground(const glm::vec4 &color);

			virtual const glm::vec2		&getMaximumSize() const;

            virtual void    draw();

			virtual void	onClick(int x, int y);

			virtual void	addSurface(Surface *surface);

			enum Behavior {
				FILL,
				CENTERED,
				DEFAULT
			};

			virtual void	setBehavior(Behavior behavior);

        protected:
			static  std::shared_ptr<gl_item::Shader> 	shader;

			std::list<Surface *>						childs;
			std::shared_ptr<gl_item::Mesh>				mesh;

			glm::vec2		_real_pos;
            glm::vec2       pos, size, max_size;
            glm::vec4       color;

			Behavior		behavior;

			virtual void	validate(const glm::vec2 &min, const glm::vec2 &max, bool validate_childs = true);
        };

    }
}

#endif /* end of include guard: FSE_UI_SURFACE_HPP */
