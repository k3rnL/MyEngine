/**
 * @Author: daniel_b
 * @Date:   2017-09-22T00:10:27+02:00
 * @Last modified by:   daniel_b
 * @Last modified time: 2018-02-12T07:10:23+01:00
 */



#ifndef MXE_GL_ITEM_BUFFER
#define MXE_GL_ITEM_BUFFER

#include <iostream>
#include <vector>

#include <GL/glew.h>
#include <glm/glm.hpp>

#include "fse/Export.hpp"

namespace fse {
    namespace gl_item {

		template <class T>
        class FSE_API_EXPORT Buffer
        {
        public:

            enum BufferType
            {
                ElementBuffer = GL_ELEMENT_ARRAY_BUFFER,
                ArrayBuffer = GL_ARRAY_BUFFER
            };

            enum BufferDrawType
            {
                StaticBuffer = GL_STATIC_DRAW,
                DynamicBuffer = GL_DYNAMIC_DRAW
            };

			Buffer(BufferType type = ArrayBuffer, BufferDrawType draw_type = StaticBuffer) {
				_type = type;
				_draw = draw_type;
				_elem_size = sizeof(T);
				glGenBuffers(1, &_id);
			}
            Buffer(Buffer<T> &buffer) {
				this->_draw = buffer._draw;
				this->_id = buffer._id;
				this->_size = buffer._size;
				this->_type = buffer._type;
			}
            ~Buffer() {
				glDeleteBuffers(1, &_id);
			}

            void    send(std::vector<T> &data) {
				_size = (GLuint) (sizeof(T) * data.size());
				bind();
				glBufferData(_type,
						     _size,
							 data.data(),
							 _draw);
				unbind();
			}

            void    bind() {
				glBindBuffer(_type, _id);
			}

            void    unbind() {
				glBindBuffer(_type, 0);
			}

            GLuint  getSize() {
				return (_size);
			}

			void    setType(BufferType type) { _type = type; }
			void    setDrawType(BufferDrawType type) { _draw = type; }

            Buffer<T>  &operator=(Buffer<T> &b) {
				this->_draw = b._draw;
				// this->_id = b._id;
				this->_elem_size = b._elem_size;
				this->_size = b._size;
				this->_type = b._type;
				return (*this);
			}

        private:
            GLuint          _id;
            GLuint          _size;
			GLuint			_elem_size;
			BufferType      _type;
            BufferDrawType  _draw;
        };

    }
}

#endif
