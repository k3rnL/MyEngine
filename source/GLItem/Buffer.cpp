/**
 * @Author: daniel_b
 * @Date:   2017-09-22T00:23:09+02:00
 * @Last modified by:   daniel_b
 * @Last modified time: 2017-11-16T06:05:22+01:00
 */

/*

#include "fse/GLItem/Buffer.hpp"

using namespace fse::gl_item;

template <class T>
Buffer<T>::Buffer(BufferType type, BufferDrawType draw_type)
{
    _type = type;
    _draw = draw_type;
	_elem_size = sizeof(T);
     glGenBuffers(1, &_id);
}

template <class T>
Buffer<T>::~Buffer() {
    glDeleteBuffers(1, &_id);
}

template <class T>
Buffer<T>::Buffer(Buffer &b)
{
    this->_draw = b._draw;
    this->_id = b._id;
    this->_size = b._size;
    this->_type = b._type;
}

template <class T>
void    Buffer<T>::send(std::vector<T> &data)
{
    _size = (GLuint) sizeof(T) * data.size();
    bind();
    glBufferData(_type,
                 _size,
                 data.data(),
                 _draw);
	GLenum err;
	while ((err = glGetError()) != GL_NO_ERROR)
	{
		std::cerr << "[ERROR] Error when sending data to GPU (" << err << ")\n";
	}
    unbind();
}

template <class T>
void    Buffer<T>::bind() {
    glBindBuffer(_type, _id);
}

template <class T>
void    Buffer<T>::unbind() {
    glBindBuffer(_type, 0);
}

template <class T>
GLuint  Buffer<T>::getSize() {
    return (_size);
}

template <class T>
Buffer<T>  &Buffer<T>::operator=(Buffer<T> &b) {
    this->_draw = b._draw;
    // this->_id = b._id;
	this->_elem_size = b._elem_size;
    this->_size = b._size;
    this->_type = b._type;
    return (*this);
}
*/