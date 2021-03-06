#include "texture2D.h"

Texture2D::Texture2D(const GLuint& width,
					 const GLuint& height,
					 const unsigned char* pix_buff,
					 const unsigned int channels,
					 const GLenum filter,
					 const GLenum wrap_mode)
					:m_width(width), m_height(height)
{
	switch (channels)
	{
	case 3:
		m_mode = GL_RGB;
		break;
	case 4:
		m_mode = GL_RGBA;
		break;
	default:
		m_mode = GL_RGBA;
		break;
	}
	
	glGenTextures(1, &m_texture_ID);
	glBindTexture(GL_TEXTURE_2D, m_texture_ID);
	glTexImage2D(GL_TEXTURE_2D, 0, m_mode, m_width, m_height, 0, m_mode, GL_UNSIGNED_BYTE, pix_buff);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap_mode);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap_mode);
	glGenerateMipmap(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, 0);
}

Texture2D::Texture2D(Texture2D&& texture2D) noexcept
{
	m_texture_ID = texture2D.m_texture_ID;
	texture2D.m_texture_ID = 0;
	m_mode = texture2D.m_mode;
	m_width = texture2D.m_width;
	m_height = texture2D.m_height;
}

Texture2D& Texture2D::operator=(Texture2D&& texture2D) noexcept
{
	glDeleteTextures(1, &m_texture_ID);
	m_texture_ID = texture2D.m_texture_ID;
	texture2D.m_texture_ID = 0;
	m_mode = texture2D.m_mode;
	m_width = texture2D.m_width;
	m_height = texture2D.m_height;
	return *this;
}

Texture2D::~Texture2D()
{
	glDeleteTextures(1, &m_texture_ID);
}

void Texture2D::bind() const
{
	glBindTexture(GL_TEXTURE_2D, m_texture_ID);
}