/**
 * @Date:   2018-02-26T01:49:19+01:00
 * @Last modified time: 2018-02-26T01:49:54+01:00
 */

#ifndef FSE_UI_LAYOUT_HPP
#define FSE_UI_LAYOUT_HPP

#include "fse/Ui/Surface.hpp"

namespace fse {
    namespace ui {

		class FSE_API_EXPORT Layout : public Surface
		{
		public:
			virtual ~Layout();

			virtual void			resizeChilds() = 0;
		protected:
			virtual void			validate(const glm::vec2 &pos, const glm::vec2 &size, bool validate_childs = true);


		};

    } /* ui */
} /* fse */

#endif /* end of include guard: FSE_UI_LAYOUT_HPP */
