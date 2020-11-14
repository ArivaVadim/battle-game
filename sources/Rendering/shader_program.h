#ifndef ShaderProgram_H
#define ShaderProgram_H

#include <glad/glad.h>
#include <string>
#include <iostream>

	class  ShaderProgram {
	public:
		explicit ShaderProgram(const GLchar* vertex_shader_program, const GLchar* fragment_shader_program);
		~ShaderProgram();
		void use() const;

		ShaderProgram() = delete;
		ShaderProgram(ShaderProgram&) = delete;
		ShaderProgram& operator=(ShaderProgram&) = delete;

	private:
		GLuint vertex_shader;
		GLuint fragment_shader;
		GLuint program;

		bool initShader(GLuint& shader, const GLenum type, const GLchar* shader_program);
		bool linkProgram(GLuint& program, const GLuint& shader1, const GLuint& shader2);
	};
	   	  
#endif // ShaderProgram_H