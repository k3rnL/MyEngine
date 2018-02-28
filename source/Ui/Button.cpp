/**
 * @Date:   2018-02-25T21:08:56+01:00
 * @Last modified time: 2018-02-25T21:09:10+01:00
 */

#include "fse/Ui/Button.hpp"

using namespace fse::ui;

Button::~Button() {

}

void	Button::onClick(int x, int y) {
	onClickCallback(x, y);
}

void			Button::setOnMouseClick(std::function<void(int, int)> fct) {
	onClickCallback = fct;
}