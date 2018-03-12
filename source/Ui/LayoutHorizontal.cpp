/**
 * @Date:   2018-02-27T16:19:46+01:00
 * @Last modified time: 2018-02-27T16:21:17+01:00
 */

#include "fse/Ui/LayoutHorizontal.hpp"

using namespace fse::ui;

LayoutHorizontal::~LayoutHorizontal() {

}

void	LayoutHorizontal::setBound(const Bound &bound) {
	this->bound = bound;
	if (!childs.size())
		return;
	Bound frame = getSurface();
	glm::vec2 position(0, 0);
	for (auto c : childs) {
		c->setBound(frame);
		Bound f = c->getSurface();
		frame.pos.x += f.size.x;
		frame.size.x -= f.size.x;
	}
}