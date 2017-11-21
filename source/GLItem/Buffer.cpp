/**
 * @Author: daniel_b
 * @Date:   2017-09-22T00:23:09+02:00
 * @Last modified by:   daniel_b
 * @Last modified time: 2017-11-16T06:05:22+01:00
 */



#include "fse/GLItem/Buffer.hpp"

using namespace fse::gl_item;

Buffer::Buffer(BufferType type, BufferDrawType draw_type)
{
    _type = type;
    _draw = draw_type;
     glGenBuffers(1, &_id);
}

Buffer::~Buffer() {
    glDeleteBuffers(1, &_id);
}

Buffer::Buffer(Buffer &b)
{
    this->_draw = b._draw;
    this->_id = b._id;
    this->_size = b._size;
    this->_type = b._type;
}

void    Buffer::send(GLuint size, void *data)
{
    _size = size;
    bind();
    glBufferData(_type,
                 size,
                 data,
                 _draw);
    unbind();
}

void    Buffer::bind() {
    glBindBuffer(_type, _id);
}

void    Buffer::unbind() {
    glBindBuffer(_type, 0);
}

GLuint  Buffer::getSize() {
    return (_size);
}

Buffer  &Buffer::operator=(Buffer &b) {
    this->_draw = b._draw;
    // this->_id = b._id;
    this->_size = b._size;
    this->_type = b._type;
    return (*this);
}
