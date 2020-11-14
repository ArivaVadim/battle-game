#ifndef ShaderProgram_H
#define ShaderProgram_H

#include <glad/glad.h>
#include <string>
#include <iostream>


	class  ShaderProgram {
	public:
		 ShaderProgram();
		 ~ShaderProgram();
		 bool initShader(const GLenum type, const GLchar* shader_program);
		 GLuint getShader();


	private:
		GLuint shader;


	};






#endif // ShaderProgram_H