/**
 * @Date:   2018-02-26T01:49:19+01:00
 * @Last modified time: 2018-02-27T16:20:44+01:00
 */

#ifndef FSE_UI_LAYOUT_HORIZONTAL_HPP
#define FSE_UI_LAYOUT_HORIZONTAL_HPP

#include  "fse/Ui/Layout.hpp"

namespace fse {
    namespace ui {

        class FSE_API_EXPORT LayoutHorizontal : public Layout
        {
		public:
			virtual ~LayoutHorizontal();

			virtual void	setBoundary(const Bound &bound);
        };

    } /* ui */
} /* fse */

#endif /* end of include guard: FSE_UI_LAYOUT_HORIZONTAL_HPP */
