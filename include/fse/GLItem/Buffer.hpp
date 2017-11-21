/**
 * @Author: daniel_b
 * @Date:   2017-09-22T00:10:27+02:00
 * @Last modified by:   daniel_b
 * @Last modified time: 2017-11-16T05:54:28+01:00
 */



#ifndef MXE_GL_ITEM_BUFFER
#define MXE_GL_ITEM_BUFFER

#include <GL/glew.h>
#include <glm/glm.hpp>

namespace fse {
    namespace gl_item {

        class Buffer
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

            Buffer(BufferType type = ArrayBuffer, BufferDrawType draw_type = StaticBuffer);
            Buffer(Buffer &buffer);
            ~Buffer();

            void    send(GLuint size, void *data);

            void    bind();
            void    unbind();

            GLuint  getSize();

            void    setType(BufferType type);
            void    setDrawType(BufferDrawType type);

            Buffer  &operator=(Buffer &b);

        private:
            GLuint          _id;
            GLuint          _size;
            BufferType      _type;
            BufferDrawType  _draw;
        };

    }
}

#endif
