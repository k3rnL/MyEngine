/**
 * @Author: daniel_b
 * @Date:   2017-11-13T01:37:42+01:00
 * @Last modified by:
 * @Last modified time: 2017-11-23T19:35:36+01:00
 */

 #include "fse/GLItem/Texture.hpp"

 #ifndef STB_IMAGE_IMPLEMENTATION
 #define STB_IMAGE_IMPLEMENTATION
 #endif
 #include <fse/Extra/stb_image.h>

 using namespace fse::gl_item;

 #include <iostream>

 std::shared_ptr<Texture>    Texture::create(size_t x, size_t y,
                                             InternalFormat in_format,
                                             Format format,
                                             Type type)
 {
     std::shared_ptr<Texture>        texture;

     texture = std::make_shared<Texture>();
     texture->bind();
     texture->_size.x = (float) x;
     texture->_size.y = (float) y;
     glTexImage2D(GL_TEXTURE_2D, 0, in_format, (GLsizei) x, (GLsizei) y, 0, format, type, 0);
     return (texture);
 }

 std::shared_ptr<Texture>    Texture::load(const std::string &file) {
     std::shared_ptr<Texture>        texture = std::make_shared<Texture>();
     int x, y, n;
     unsigned char   *data = stbi_load(file.c_str(), &x, &y, &n, 0);

     texture->bind();
     if (!data){
         std::cerr << "[ERROR] Cannot load " << file << "\n";
         return 0;
     }
     texture->activate(0);
     glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, x, y, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
     texture->_size.x = (float) x;
     texture->_size.y = (float) y;

     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 4); // pick mipmap level 7 or lower
     glGenerateMipmap(GL_TEXTURE_2D);

     // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
     // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
     return (texture);
 }

 Texture::Texture() {
     glGenTextures(1, &_id);
 }

 Texture::~Texture() {
     glDeleteTextures(1, &_id);
 }

 void    Texture::activate(int slot) {
     glActiveTexture(GL_TEXTURE0 + slot);
     bind();
 }

 void    Texture::bind() {
     glBindTexture(GL_TEXTURE_2D, _id);
 }

 void    Texture::unbind() {
     glBindTexture(GL_TEXTURE_2D, 0);
 }

 GLuint  Texture::getId() {
     return (_id);
 }

 void    Texture::setMipMapLevel(int level) {
     bind();
     if (level)
         glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
     else
         glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, level); // pick mipmap level 7 or lower
 }
