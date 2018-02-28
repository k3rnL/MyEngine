/**
 * @Date:   2018-02-23T01:01:21+01:00
 * @Last modified time: 2018-02-23T01:04:24+01:00
 */

#include "fse/Ui/Surface.hpp"

using namespace fse::ui;

std::shared_ptr<fse::gl_item::Shader> Surface::shader = 0;

Surface::Surface() : _real_pos(0), pos(0), size(0), max_size(0), behavior(DEFAULT) {
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

void	Surface::addSurface(Surface *surface) {
	childs.push_back(surface);
	surface->validate(pos, size + _real_pos);
}

void	Surface::onClick(int x, int y) {
	for (auto c : childs) {
		if (c->pos.x < x && c->pos.x + c->size.x > x)
			if (c->pos.y < y && c->pos.y + c->size.y > y)
				c->onClick(x, y);
	}
}

void	Surface::setMaximumSize(const glm::vec2 &m) {
	max_size = m;
}

void	Surface::setSize(const glm::vec2 &s) {
	size = s;
}

void	Surface::setPos(const glm::vec2 &p) {
	pos = p;
}

void    Surface::setBackground(const glm::vec4 &color) {
    this->color = color;
}

void    Surface::draw() {
    shader->useProgram();
	mesh->bindToShader(shader);
	shader->setUniformValue(color, "color");
	glViewport(_real_pos.x, _real_pos.y, size.x, size.y);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
	for (auto c : childs) {
		c->draw();
	}
}

void	Surface::validate(const glm::vec2 &min, const glm::vec2 &max, bool validate_childs) {
	if (behavior == FILL) {
		_real_pos = min;
		setSize(max - min);
	}
	else if (behavior == CENTERED) {
		glm::vec2 s = glm::clamp(getMaximumSize(), glm::vec2(0), max - min);
		setSize(s);
		_real_pos = max - min - s / 4.f;
	}
	else if (behavior == DEFAULT) {
		_real_pos = min + pos;
		glm::vec2 m = glm::clamp(this->size, glm::vec2(0), max - _real_pos);
		if (max_size.x > 0)
			m.x = glm::clamp(m.x, .0f, max_size.x);
		if (max_size.y > 0)
			m.y = glm::clamp(m.y, .0f, max_size.y);
		setSize(glm::clamp(this->size, glm::vec2(0), m));
	}
	if (validate_childs)
		for (auto c : childs) {
			c->validate(this->_real_pos, this->_real_pos + this->size);
		}
}

const glm::vec2		&Surface::getMaximumSize() const {
	return (max_size);
}

void				Surface::setBehavior(Behavior behavior) {
	this->behavior = behavior;
}