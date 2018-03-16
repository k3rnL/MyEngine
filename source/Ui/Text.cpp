/**
 * @Date:   2018-02-24T06:47:52+01:00
 * @Last modified time: 2018-03-15T10:14:38+01:00
 */

#include "fse/Ui/Text.hpp"

using namespace fse::ui;

FT_Library	*Text::ft = 0;
std::shared_ptr<fse::gl_item::Shader>	Text::shader = 0;

Text::Text() {
	if (ft == 0) {
		ft = new FT_Library;
		FT_Init_FreeType(ft);
	}
	if (shader == 0)
		shader = std::make_shared<fse::gl_item::Shader>("shader/text.vert", "shader/text.frag");
	texture = gl_item::Texture::create(0, 0, fse::gl_item::Texture::InternalFormat::RED8, fse::gl_item::Texture::RED, fse::gl_item::Texture::Type::UNSIGNED_BYTE);
	texture->setMipMapLevel(0);
	setBehavior(new Fill());
	setBackground(glm::vec4(0, 0, 0, 0));
	text_color = glm::vec4(0, 0, 0, 1);

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

	shader->setAttribute(vertex_buffer, 0, 3);
	shader->setAttribute(uv_buffer, 1, 2);
}

Text::Text(const std::string &txt) {
	if (ft == 0) {
		ft = new FT_Library;
		FT_Init_FreeType(ft);
	}
	setText(txt);
}

Text::~Text() {
	delete ft;
}

void	Text::draw(Drawer &drawer) {
	Surface::draw(drawer);
	Bound bound = getSurface();
	FT_Set_Pixel_Sizes(face, 0, bound.size.y);
	for (auto c : text) {
		if (FT_Load_Char(face, c, FT_LOAD_RENDER)) {
			//pos.x += size.y * 0.75;
			continue;
		}

		int sizey = face->glyph->bitmap.rows;
		int posy = bound.pos.y - face->glyph->bitmap_top + bound.size.y * 0.75;
		int posx = bound.pos.x + face->glyph->bitmap_left;
		int sizex = face->glyph->bitmap.width;
		vertexes[0] = glm::vec3( posx / drawer.getSize().x * 2.0 - 1,           posy / drawer.getSize().y * 2.0 - 1, 0);
		vertexes[1] = glm::vec3((posx + sizex) / drawer.getSize().x * 2.0 - 1,  posy / drawer.getSize().y * 2.0 - 1, 0);
		vertexes[2] = glm::vec3((posx + sizex) / drawer.getSize().x * 2.0 - 1,  (posy + sizey) / drawer.getSize().y * 2.0 - 1, 0);
		vertexes[3] = glm::vec3( posx / drawer.getSize().x * 2.0 - 1,           (posy + sizey) / drawer.getSize().y * 2.0 - 1, 0);
		vertex_buffer.send(vertexes);

		shader->useProgram();
		shader->setAttribute(vertex_buffer, 0, 3);
		//drawer.viewPort({ posx, posy + bound.size.y * 0.25 }, { maxx, sizey });
		texture->size.x = face->glyph->bitmap.width;
		texture->size.y = face->glyph->bitmap.rows;
		texture->data(face->glyph->bitmap.buffer);

		//mesh->bindToShader(shader);
		texture->activate(0);
		shader->setUniformValue(text_color, "color");
		shader->setUniformValue(0, "font");
		glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

		bound.pos.x += face->glyph->advance.x >> 6;
	}
}

void Text::setTextColor(const glm::vec4 & color) {
	text_color = color;
}

void	Text::setText(const std::string &t) {
	text = t;
}

const std::string	&Text::getText() const {
	return (text);
}

void	Text::setFont(const std::string &file) {
	FT_New_Face(*ft, file.c_str(), 0, &face);
}

void	Text::setSize(const glm::vec2 &size) {
	setBehavior(new FitTo(glm::vec2(0, size.y)));
	FT_Set_Pixel_Sizes(face, 0, size.y);
}
