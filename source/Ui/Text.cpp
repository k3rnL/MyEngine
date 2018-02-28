/**
 * @Date:   2018-02-24T06:47:52+01:00
 * @Last modified time: 2018-02-24T06:47:52+01:00
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
	setBehavior(FILL);
	setBackground(glm::vec4(0, 0, 0, 0));
	text_color = glm::vec4(0, 0, 0, 1);
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

void	Text::draw() {
	Surface::draw();
	glm::vec2 pos = this->_real_pos;
	for (auto c : text) {
		if (FT_Load_Char(face, c, FT_LOAD_RENDER)) {
			//pos.x += size.y * 0.75;
			continue;
		}
		int bottom = size.y - face->glyph->bitmap_top;
		int sizey = face->glyph->bitmap.rows;
		int posy = pos.y + face->glyph->bitmap_top - sizey;
		int posx = pos.x + face->glyph->bitmap_left;
		int maxx = face->glyph->bitmap.width;
		glViewport(posx, posy + size.y * 0.25, maxx, sizey);
		texture->size.x = face->glyph->bitmap.width;
		texture->size.y = face->glyph->bitmap.rows;
		texture->data(face->glyph->bitmap.buffer);

		shader->useProgram();
		mesh->bindToShader(shader);
		texture->activate(0);
		shader->setUniformValue(text_color, "color");
		shader->setUniformValue(0, "font");
		glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

		pos.x += face->glyph->advance.x >> 6;
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
	Surface::setSize(size);
	//FT_Set_Char_Size(face, 0, size.y * 32, 300, 300);
	FT_Set_Pixel_Sizes(face, 0, size.y);
}