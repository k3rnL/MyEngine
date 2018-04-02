/**
 * @Date:   2018-02-23T00:46:33+01:00
 * @Last modified time: 2018-03-16T20:51:33+01:00
 */
#ifndef FSE_UI_SURFACE_HPP
#define FSE_UI_SURFACE_HPP

#include <glm/glm.hpp>

#include <list>
#include <typeindex>

#include "fse/Export.hpp"
#include "fse/GLItem/Texture.hpp"
#include "fse/GLItem/Shader.hpp"
#include "fse/GLItem/Mesh.hpp"

#include "fse/Ui/Drawer.hpp"

namespace fse {
    namespace ui {

        class FSE_API_EXPORT Surface {
        public:
			Surface();
			virtual ~Surface() {}

            virtual void    setBackground(const glm::vec4 &color);



			virtual void	onClick(int x, int y);
			virtual void	onClickReleased(int x, int y);

			virtual void	addSurface(Surface *surface);

      std::shared_ptr<gl_item::Shader>  getShader() { return shader; }
      void                              setShader(std::shared_ptr<gl_item::Shader> shader) { this->shader = shader; }

			class Bound {
			public:
				glm::vec2 pos;
				glm::vec2 size;
			};

			virtual void    draw(Drawer &drawer);

			class Behavior {
			public:
				virtual ~Behavior() {}
				virtual void	transform(Bound &parent_bound, Bound &frame) = 0;
			};

			class Fill : public Behavior {
			public:
				virtual void	transform(Bound &parent_bound, Bound &frame) {
					frame.pos = parent_bound.pos;
					frame.size = parent_bound.size;
				}
			};

			class FitTo : public Behavior {
			public:
				virtual ~FitTo() {}
				FitTo(const glm::vec2 &size) : mSize(size) {}

				virtual void	transform(Bound &parent_bound, Bound &frame) {
					Bound &b = parent_bound;
					if (mSize.x > 0)
						b.size.x = mSize.x;
					if (mSize.y > 0)
						b.size.y = mSize.y;
					frame = b;
				}

				const glm::vec2		mSize;
			};

			class RelativePosition : public Behavior {
			public:
				virtual ~RelativePosition() {}
				RelativePosition(const glm::vec2 &position) : mPos(position) {}

				virtual void	transform(Bound &parent_bound, Bound &frame) {
					frame.pos += mPos;
				}

				const glm::vec2		mPos;
			};

			class AbsolutePosition : public Behavior {
			public:
				virtual ~AbsolutePosition() {}
				AbsolutePosition(const glm::vec2 &position) : mPos(position) {}

				virtual void	transform(Bound &parent_bound, Bound &frame) {
					parent_bound.pos = mPos;
				}

				const glm::vec2		mPos;
			};

			class Margin : public Behavior {
			public:
				virtual ~Margin() {}
				Margin(int top, int left, int bottom, int right) : mMargin(top, left, bottom, right) {}
				Margin(int all) : mMargin(all) {}

				virtual void	transform(Bound &parent_bound, Bound &frame) {
					Bound &b = frame;
					b.pos.x += mMargin.x;
					b.pos.y += mMargin.y;
					b.size.y -= mMargin.z + mMargin.x;
					b.size.x -= mMargin.w + mMargin.y;
				}

				const glm::vec4		mMargin;
			};

			template <class T>
			FSE_API_EXPORT T	*getBehavior() {
				return (T *)behaviors[typeid (T)];
			}

			template <class T>
			FSE_API_EXPORT void	setBehavior(T *behavior) {
				behaviors[typeid (T)] = behavior;
			}

			virtual Bound	&getFrame();
			virtual Bound	&getBound();
			virtual void	setBoundary(const Bound &bound);

			virtual void update();

        protected:
			static  std::shared_ptr<gl_item::Shader> 	default_shader;
			std::shared_ptr<gl_item::Shader>          shader;
			std::list<Surface *>						childs;
			std::shared_ptr<gl_item::Mesh>				mesh;

            glm::vec4       color;

			Bound			bound;
			Bound			parent_bound;
			Bound			frame;

			std::map < std::type_index, Behavior * > behaviors;

        };

    }
}

#endif /* end of include guard: FSE_UI_SURFACE_HPP */
