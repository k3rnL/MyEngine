/**
 * @Date:   2018-02-26T01:49:19+01:00
 * @Last modified time: 2018-02-27T16:19:35+01:00
 */

#ifndef FSE_UI_LAYOUT_VERTICAL_HPP
#define FSE_UI_LAYOUT_VERTICAL_HPP

#include  "fse/Ui/Layout.hpp"

namespace fse {
    namespace ui {

        class FSE_API_EXPORT LayoutVertical : public Layout
        {
		public:
			virtual ~LayoutVertical();

			virtual void	resizeChilds();
        };

    } /* ui */
} /* fse */

#endif /* end of include guard: FSE_UI_LAYOUT_VERTICAL_HPP */
