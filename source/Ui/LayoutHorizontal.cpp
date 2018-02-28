/**
 * @Date:   2018-02-27T16:19:46+01:00
 * @Last modified time: 2018-02-27T16:21:17+01:00
 */

#include "fse/Ui/LayoutHorizontal.hpp"

using namespace fse::ui;

LayoutHorizontal::~LayoutHorizontal() {

}

void	LayoutHorizontal::resizeChilds() {
	if (!childs.size())
		return;

	glm::vec2 size(size.x / childs.size(), size.y);
	glm::vec2 position(0, 0);
	for (auto c : childs) {
		glm::vec2 s = size;
		if (c->getMaximumSize().x > 0)
			s.x = glm::clamp(s.x, .0f, c->getMaximumSize().x);
		if (c->getMaximumSize().y > 0)
			s.y = glm::clamp(s.y, .0f, c->getMaximumSize().y);
		position.x += s.x;
		c->setPos(position);
		c->setSize(s);
	}
}