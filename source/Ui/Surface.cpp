/**
 * @Date:   2018-02-23T01:01:21+01:00
 * @Last modified time: 2018-02-23T01:04:24+01:00
 */

#include "fse/Ui/Surface.hpp"

using namespace fse::ui;

std::shared_ptr<fse::gl_item::Shader> Surface::shader = 0;

Surface::Surface() {
	if (shader == 0)
		shader = std::make_shared<fse::gl_item::Shader>("shader/ui.vert", "shader/ui.frag");

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

Surface::Bound	Surface::getSurface() {
	Bound new_bound = bound;
	for (auto behavior : behaviors) {
		new_bound = behavior.second->transform(new_bound);
	}
	return (new_bound);
}

void	Surface::addSurface(Surface *surface) {
	childs.push_back(surface);
	surface->setBound(getSurface());
}

void	Surface::setBound(const Bound &b) {
	bound = b;
	Bound surface = getSurface();
	for (auto s : childs) {
		s->setBound(surface);
	}
}

void	Surface::onClick(int x, int y) {
	for (auto c : childs) {
		const Bound surface = c->getSurface();
			if (surface.pos.x < x && surface.pos.x + surface.size.x > x)
			if (surface.pos.y < y && surface.pos.y + surface.size.y > y)
				c->onClick(x, y);
	}
}

void    Surface::setBackground(const glm::vec4 &color) {
    this->color = color;
}

void    Surface::draw() {
	Bound bound = getSurface();
    shader->useProgram();
	mesh->bindToShader(shader);
	shader->setUniformValue(color, "color");
	glViewport(bound.pos.x, bound.pos.y, bound.size.x, bound.size.y);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
	for (auto c : childs) {
		c->draw();
	}
}