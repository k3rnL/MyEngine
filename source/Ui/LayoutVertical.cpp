/**
 * @Date:   2018-02-27T16:19:46+01:00
 * @Last modified time: 2018-02-27T16:20:00+01:00
 */

#include "fse/Ui/LayoutVertical.hpp"

using namespace fse::ui;

LayoutVertical::~LayoutVertical() {

}

void	LayoutVertical::setBound(const Bound &bound) {
	this->bound = bound;
	if (!childs.size())
		return;
	Bound frame = getSurface();
	glm::vec2 position(0, 0);
	for (auto c : childs) {
		c->setBound(frame);
		Bound f = c->getSurface();
		frame.pos.y += f.size.y;
		frame.size.y -= f.size.y;
	}
}