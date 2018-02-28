/**
 * @Date:   2018-02-25T21:08:21+01:00
 * @Last modified time: 2018-02-25T21:08:45+01:00
 */

#ifndef FSE_UI_BUTTON_HPP
#define FSE_UI_BUTTON_HPP

#include <functional>

#include "fse/Ui/Surface.hpp"
#include "fse/Ui/Text.hpp"

namespace fse {
    namespace ui {

		class FSE_API_EXPORT Button : public Surface
		{
		public:
			virtual ~Button();

			virtual void	onClick(int x, int y);

			void			setOnMouseClick(std::function<void(int, int)> function);
		private:
			std::function<void(int, int)>	onClickCallback;
		};

    } /* ui */
} /* fse */

#endif /* end of include guard: FSE_UI_BUTTON_HPP */
