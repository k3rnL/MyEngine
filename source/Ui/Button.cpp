/**
 * @Date:   2018-02-25T21:08:56+01:00
 * @Last modified time: 2018-02-25T21:09:10+01:00
 */

#include "fse/Ui/Button.hpp"

using namespace fse::ui;

Button::Button() {
	mPressed = false;
}

Button::~Button() {

}

void	Button::onClick(int x, int y) {
	const Bound &surface = getFrame();
	if (surface.pos.x < x && surface.pos.x + surface.size.x > x)
		if (surface.pos.y < y && surface.pos.y + surface.size.y > y) {
			onClickCallback(x, y);
			mPressed = true;
		}
}

void	Button::onClickReleased(int x, int y) {
	const Bound &surface = getFrame();
	if (surface.pos.x < x && surface.pos.x + surface.size.x > x)
		if (surface.pos.y < y && surface.pos.y + surface.size.y > y) {
			onClickReleasedCallback(x, y);
			mPressed = false;
		}
}

void			Button::setOnMouseClick(std::function<void(int, int)> fct) {
	onClickCallback = fct;
}

void			Button::setOnMouseClickReleased(std::function<void(int, int)> fct) {
	onClickReleasedCallback = fct;
}

void    Button::draw(Drawer &drawer) {

	if (!mPressed)
		drawer.drawRoundedRect(frame.pos, frame.size, getFrame().size.y/2, color);
	else
		drawer.drawRoundedRect(frame.pos, frame.size, getFrame().size.y / 2, color * glm::vec4(0.85,0.85,0.85,1));
	for (auto c : childs) {
		c->draw(drawer);
	}
}
