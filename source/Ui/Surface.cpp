/**
 * @Date:   2018-02-23T01:01:21+01:00
 * @Last modified time: 2018-03-16T20:52:10+01:00
 */

#include "fse/Ui/Surface.hpp"

using namespace fse::ui;

std::shared_ptr<fse::gl_item::Shader> Surface::default_shader = 0;

Surface::Surface() {
	if (default_shader == 0)
		default_shader = std::make_shared<fse::gl_item::Shader>("shader/ui.vert", "shader/ui.frag");
	shader = default_shader;
	mesh = std::make_shared<fse::gl_item::Mesh>();

	mesh->addVertex(glm::vec3(-1, -1, 0));
	mesh->addVertex(glm::vec3( 1, -1, 0));
	mesh->addVertex(glm::vec3( 1,  1, 0));
	mesh->addVertex(glm::vec3(-1,  1, 0));
	mesh->addUV(glm::vec2(0, 0));
	mesh->addUV(glm::vec2(1, 0));
	mesh->addUV(glm::vec2(1, 1));
	mesh->addUV(glm::vec2(0, 1));
	mesh->finish();
}

void	Surface::update() {
	bound = parent_bound;
	frame = bound;
	for (auto behavior : behaviors) {
		behavior.second->transform(bound, frame);
	}
}

void	Surface::addSurface(Surface *surface) {
	childs.push_back(surface);
	surface->setBoundary(getFrame());
}

Surface::Bound	&Surface::getFrame() {
	return (frame);
}

Surface::Bound	&Surface::getBound() {
	return bound;
}

void	Surface::setBoundary(const Bound &b) {
	parent_bound = b;
	update();
	for (auto s : childs) {
		s->setBoundary(frame);
	}
}

void	Surface::onClick(int x, int y) {
	for (auto c : childs) {
		c->onClick(x, y);
	}
}

void	Surface::onClickReleased(int x, int y) {
	for (auto c : childs) {
		c->onClickReleased(x, y);
	}
}

void    Surface::setBackground(const glm::vec4 &color) {
    this->color = color;
}

void    Surface::draw(Drawer &drawer) {

	drawer.drawRect(frame.pos, frame.size, color);
	for (auto c : childs) {
		c->draw(drawer);
	}
}
