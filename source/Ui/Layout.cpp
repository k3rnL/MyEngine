/**
 * @Date:   2018-02-26T01:50:13+01:00
 * @Last modified time: 2018-02-26T01:50:24+01:00
 */

#include "fse/Ui/Layout.hpp"

using namespace fse::ui;

Layout::~Layout() {

}

void	Layout::validate(const glm::vec2 &min, const glm::vec2 &max, bool validate_childs) {
	Surface::validate(min, max, false);
	resizeChilds();
	Surface::validate(min, max, validate_childs);
}