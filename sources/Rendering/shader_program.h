#ifndef ShaderProgram_H
#define ShaderProgram_H

#include <glad/glad.h>
#include <string>
#include <iostream>

class  ShaderProgram {
public:
	ShaderProgram(const std::string& vertex_shader_program, const std::string& fragment_shader_program);
	~ShaderProgram();
	void useShaderProgram() const;

	ShaderProgram() = delete;
	ShaderProgram(ShaderProgram&) = delete;
	ShaderProgram& operator=(ShaderProgram&) = delete;

	bool isCompile;
private:
	GLuint vertex_shader;
	GLuint fragment_shader;
	GLuint program;

	bool initShader(GLuint& shader, const GLenum type, const std::string& shader_program);
	bool linkProgram(GLuint& program, const GLuint& shader1, const GLuint& shader2);
};
	   	  
#endif // ShaderProgram_H