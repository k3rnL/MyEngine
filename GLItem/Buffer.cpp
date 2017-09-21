/**
 * @Author: daniel_b
 * @Date:   2017-09-22T00:23:09+02:00
 * @Last modified by:   daniel_b
 * @Last modified time: 2017-09-22T00:24:22+02:00
 */



#include "GLItem/Buffer.hpp"

Buffer::Buffer(BufferType type, BufferDrawType draw_type)
{
    _type = type;
    _draw = draw_type;
}
