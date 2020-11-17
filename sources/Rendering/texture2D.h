#ifndef Texture2D_H
#define Texture2D_H_H

#include <glad/glad.h>
#include <string>
#include <iostream>

class  Texture2D {
public:
	Texture2D(const GLuint& width, 
			  const GLuint& height, 
			  const unsigned char* pix_buff, 
			  const unsigned int channels = 4, 
			  const GLenum filter = GL_LINEAR, 
			  const GLenum wrap_mode = GL_CLAMP_TO_EDGE);
	Texture2D(Texture2D&&) noexcept;
	Texture2D& operator=(Texture2D&&) noexcept;
	~Texture2D();
	void bind() const;
	
	
	
	Texture2D() = delete;
	Texture2D(const Texture2D&) = delete;
	Texture2D& operator=(const Texture2D&) = delete;

private:
	GLenum m_mode;
	GLuint m_texture_ID;
	unsigned int m_width;
	unsigned int m_height;

};
	   	  
#endif // Texture2D_H