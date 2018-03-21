/**
 * @Date:   2018-02-25T21:08:21+01:00
 * @Last modified time: 2018-02-28T16:50:13+01:00
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
			Button();
			virtual ~Button();

			virtual void	onClick(int x, int y);
			virtual void	onClickReleased(int x, int y);
 
			bool			isPressed();

			void			setOnMouseClick(std::function<void(int, int)> function);
			void			setOnMouseClickReleased(std::function<void(int, int)> function);

			virtual void    draw(Drawer &drawer);

		private:
			bool							mPressed;

			std::function<void(int, int)>	onClickCallback;
			std::function<void(int, int)>	onClickReleasedCallback;
		};

    } /* ui */
} /* fse */

#endif /* end of include guard: FSE_UI_BUTTON_HPP */
