/**
 * @Date:   2018-02-27T16:19:46+01:00
 * @Last modified time: 2018-02-27T16:20:00+01:00
 */

#include "fse/Ui/LayoutVertical.hpp"

using namespace fse::ui;

LayoutVertical::~LayoutVertical() {

}

void	LayoutVertical::resizeChilds() {
	if (!childs.size())
		return;

	glm::vec2 size(size.x, size.y / childs.size());
	glm::vec2 position(0, this->size.y);
	for (auto c : childs) {
		glm::vec2 s = size;
		if (c->getMaximumSize().x > 0)
			s.x = glm::clamp(s.x, .0f, c->getMaximumSize().x);
		if (c->getMaximumSize().y > 0)
			s.y = glm::clamp(s.y, .0f, c->getMaximumSize().y);
		position.y -= s.y;
		c->setPos(position);
		c->setSize(s);
	}
}