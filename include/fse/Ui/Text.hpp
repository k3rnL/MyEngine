/**
 * @Date:   2018-02-24T06:47:40+01:00
 * @Last modified time: 2018-03-12T21:21:58+01:00
 */

#ifndef FSE_UI_TEXT_HPP
#define FSE_UI_TEXT_HPP

#include <string>

#include <ft2build.h>
#include FT_FREETYPE_H

#include "fse/Export.hpp"
#include "fse/Ui/Surface.hpp"

namespace fse {
    namespace ui {

        class FSE_API_EXPORT Text : public Surface
        {
		public:
			Text();
			Text(const std::string &txt);
			virtual ~Text();

			virtual void		setSize(const glm::vec2 &size);

			void				setText(const std::string &text);
			const std::string	&getText() const;

			void				setFont(const std::string &file);
			void				setTextColor(const glm::vec4 &color);

			virtual void    draw();

		private:
			static FT_Library					*ft;
			FT_Face								face;
			std::shared_ptr<gl_item::Texture>	texture;
			static std::shared_ptr<gl_item::Shader>	shader;
			std::string							text;
			glm::vec4							text_color;
        };

    } /* ui */
} /* fse */

#endif /* end of include guard: FSE_UI_TEXT_HPP */
