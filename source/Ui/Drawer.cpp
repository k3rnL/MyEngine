/**
 * @Date:   2018-03-13T00:22:16+01:00
 * @Last modified time: 2018-03-13T00:22:28+01:00
 */

#include "fse/Ui/Drawer.hpp"

using namespace fse::ui;

Drawer::Drawer(const glm::vec2 &size) : 
	size(size), 
	vertex_buffer(gl_item::Buffer<glm::vec3>::ArrayBuffer, gl_item::Buffer<glm::vec3>::DynamicBuffer) 
{
	shader = std::make_shared<fse::gl_item::Shader>("shader/ui.vert", "shader/ui.frag");

	vertexes.push_back(glm::vec3(-1, -1, 0));
	vertexes.push_back(glm::vec3(1, -1, 0));
	vertexes.push_back(glm::vec3(1, 1, 0));
	vertexes.push_back(glm::vec3(-1, 1, 0));
	

	static glm::vec2 uvs[] = {
		glm::vec2(0, 0),
		glm::vec2(1, 0),
		glm::vec2(1, 1),
		glm::vec2(0, 1)
	};

	vertex_buffer.send(vertexes);
	uv_buffer.send(uvs, 4);

}

void	Drawer::drawRect(const glm::vec2 &pos, const glm::vec2 &size, const glm::vec4 &color) {
	vertexes[0] = glm::vec3(pos.x / this->size.x * 2.0 - 1, pos.y / this->size.y * 2.0 - 1, 0);
	vertexes[1] = glm::vec3((pos.x + size.x) / this->size.x * 2.0 - 1, pos.y / this->size.y * 2.0 - 1, 0);
	vertexes[2] = glm::vec3((pos.x + size.x) / this->size.x * 2.0 - 1, (pos.y + size.y) / this->size.y * 2.0 - 1, 0);
	vertexes[3] = glm::vec3(pos.x / this->size.x * 2.0 - 1, (pos.y + size.y) / this->size.y * 2.0 - 1, 0);
	vertex_buffer.send(vertexes);
	shader->useProgram();
	shader->setUniformValue(color, "color");
	shader->setAttribute(vertex_buffer, 0, 3);
	shader->setAttribute(uv_buffer, 1, 2);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
}

void	Drawer::viewPort(const glm::vec2 &pos, const glm::vec2 &size) {
	//glViewport(pos.x, pos.y - size.y, size.x, size.y);

}