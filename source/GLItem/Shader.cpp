/**
 * @Author: danielb
 * @Date:   2017-07-23T01:44:16+02:00
 * @Last modified by:
 * @Last modified time: 2018-02-14T02:16:13+01:00
 */

 #include "fse/GLItem/Shader.hpp"

 using namespace fse::gl_item;

 Shader::Shader()
 {
     _programID = glCreateProgram();
 }

 Shader::~Shader()
 {
     glDeleteProgram(_programID);
 }

 Shader::Shader(const std::string &compute)
 {
     _programID = glCreateProgram();

     GLuint computeID = compile(compute, GL_COMPUTE_SHADER);
     _attached_shader[GL_COMPUTE_SHADER] = std::make_tuple(computeID, compute);

     link();
 }

 Shader::Shader(const std::string &vertex, const std::string &fragment)
 {
     _programID = glCreateProgram();

     GLuint vertexID = compile(vertex, GL_VERTEX_SHADER);
     GLuint fragmentID = compile(fragment, GL_FRAGMENT_SHADER);

     _attached_shader[GL_VERTEX_SHADER] = std::make_tuple(vertexID, vertex);
     _attached_shader[GL_FRAGMENT_SHADER] = std::make_tuple(fragmentID, fragment);

     link();
 }

 void				Shader::updateShader() {
	 auto		old_shaders = _attached_shader;
	 GLuint		old_program = _programID;

	 _attached_shader.clear();
	 try 
	 {
		 for (auto shader : old_shaders) {
			 addShader(std::get<1>(shader.second), (ShaderType) shader.first);
		 }
		 _programID = glCreateProgram();
		 link();

		 for (auto old_shader : old_shaders) {
			 glDeleteShader(std::get<0>(old_shader));
		 }
		 glDeleteProgram(old_program);
	 }
	 catch (const std::exception&)
	 {
		 _programID = old_program;
		 _attached_shader = old_shaders;
		 std::cerr << "[WARNING] Cannot update shader due to compilation/linkage error, previous version is used to prevent crashes." << std::endl;
	 }
 }

 void                Shader::addShader(const std::string &file, const fse::gl_item::Shader::ShaderType &type)
 {
     _attached_shader[type] = std::make_tuple(compile(file, type), file);
 }

 void                Shader::link()
 {
     for (auto shader : _attached_shader) {
         glAttachShader(_programID, std::get<0>(shader.second));
     }
     glLinkProgram(_programID);

     GLint error = 0;
     glGetProgramiv(_programID, GL_LINK_STATUS, &error);
     if (error != GL_TRUE)
     {
         std::cerr << "Cannot link shader.\n";
		 GLint maxLength = 0;
		 glGetProgramiv(_programID, GL_INFO_LOG_LENGTH, &maxLength);

		 // The maxLength includes the NULL character
		 std::vector<GLchar> infoLog(maxLength);
		 glGetProgramInfoLog(_programID, maxLength, &maxLength, &infoLog[0]);
         std::cerr << &infoLog[0] << "\n";
         throw std::exception();
     }
 }

 void                Shader::useProgram()
 {
     glUseProgram(_programID);
 }
 /*
 template <typename T>
 void                Shader::setAttribute(Buffer<T> &buffer, GLuint attr, GLuint n_component)
 {
     glEnableVertexAttribArray(attr);
     buffer.bind();
     glVertexAttribPointer(
         attr,               // attribute must match the layout in the shader.
         n_component,      // size
         GL_FLOAT,           // type
         GL_FALSE,           // normalized?
         0,                  // stride
         (void*)0            // array buffer offset
         );
 }*/

 void                Shader::setUniformValue(const glm::mat4 &matrix, const std::string &name)
 {
   GLuint id = glGetUniformLocation(_programID, name.c_str());
   glProgramUniformMatrix4fv(_programID, id, 1, GL_FALSE, &matrix[0][0]);
 }

 void                Shader::setUniformValue(const glm::vec3 &vec, const std::string &name)
 {
   GLuint id = glGetUniformLocation(_programID, name.c_str());
   glProgramUniform3fv(_programID, id, 1, &vec[0]);
 }

 void                Shader::setUniformValue(const int value, const std::string &name)
 {
   GLuint id = glGetUniformLocation(_programID, name.c_str());
   glProgramUniform1i(_programID, id, value);
 }

 void                Shader::setUniformValue(const unsigned int value, const std::string &name)
 {
	 GLuint id = glGetUniformLocation(_programID, name.c_str());
	 glProgramUniform1ui(_programID, id, value);
 }

 void                Shader::setUniformValue(const float value, const std::string &name)
 {
   GLuint id = glGetUniformLocation(_programID, name.c_str());
   glProgramUniform1f(_programID, id, value);
 }

 GLuint              Shader::compile(const std::string &source, GLenum type)
 {
     GLuint          id;
     std::ifstream   source_file(source);
     std::string    line;
     std::string     src;

     id = glCreateShader(type);
     while (std::getline(source_file, line))
         src += line + "\n";

     const GLchar *gl_src = src.c_str();
     glShaderSource(id, 1, &gl_src, 0);
     glCompileShader(id);

     GLint compile_error = 0;
     glGetShaderiv(id, GL_COMPILE_STATUS, &compile_error);
     if (compile_error != GL_TRUE)
     {
         std::cerr << "Cannot compile " + source + "\n";
         int log_length = 0;
         glGetShaderiv(id, GL_INFO_LOG_LENGTH, &log_length);
         std::string VertexShaderErrorMessage;
         VertexShaderErrorMessage.resize(log_length + 1);
 		glGetShaderInfoLog(id, log_length, NULL, &VertexShaderErrorMessage[0]);
         std::cerr << VertexShaderErrorMessage << "\n";
         throw std::exception();
     }
     return (id);
 }

 GLuint  Shader::getProgram()
 {
     return (_programID);
 }
