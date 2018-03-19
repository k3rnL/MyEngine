/**
 * @Date:   2018-02-27T16:19:46+01:00
 * @Last modified time: 2018-02-27T16:20:00+01:00
 */

#include "fse/Ui/LayoutVertical.hpp"

using namespace fse::ui;

LayoutVertical::~LayoutVertical() {

}

void	LayoutVertical::setBoundary(const Bound &bound) {
	Surface::setBoundary(bound);
	if (!childs.size())
		return;
	Bound frame = getFrame();
	glm::vec2 position(0, 0);
	for (auto c : childs) {
		c->setBoundary(frame);
		//c->bound;
		Bound f = c->getBound();
		frame.pos.y += f.size.y;
		frame.size.y -= f.size.y;
	}
}