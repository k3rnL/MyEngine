/**
 * @Date:   2018-02-27T16:19:46+01:00
 * @Last modified time: 2018-02-27T16:21:17+01:00
 */

#include "fse/Ui/LayoutHorizontal.hpp"

using namespace fse::ui;

LayoutHorizontal::~LayoutHorizontal() {

}

void	LayoutHorizontal::setBoundary(const Bound &bound) {
	Surface::setBoundary(bound);
	if (!childs.size())
		return;
	Bound frame = getFrame();
	glm::vec2 position(0, 0);
	for (auto c : childs) {
		c->setBoundary(frame);
		Bound f = c->getBound();
		frame.pos.x += f.size.x;
		frame.size.x -= f.size.x;
	}
}