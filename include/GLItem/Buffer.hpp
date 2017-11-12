/**
 * @Author: daniel_b
 * @Date:   2017-09-22T00:10:27+02:00
 * @Last modified by:   daniel_b
 * @Last modified time: 2017-09-22T00:27:51+02:00
 */



#ifndef MXE_GL_ITEM_BUFFER
#define MXE_GL_ITEM_BUFFER

namespace mxe {
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
            ~Buffer();

            void    send(GLuint size, void *data);

            void    setType(BufferType type);
            void    setDrawType(BufferDrawType type);

        private:
            BufferType      _type;
            BufferDrawType  _draw;
        }

    }
}

#endif
