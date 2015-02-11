#ifndef GLSL_TEXTURE_SAMPLER
#define GLSL_TEXTURE_SAMPLER

#include<GL\glew.h>
#include<GL\GL.h>

class Texture {
protected:
	GLuint m_texId; //our texture id
	const char* m_name; //our sampler name in the shader
	GLenum m_texNum; //the number id for our texture, GL_TEXTURE0 , GL_TEXTURE1 .. ect

public:
	Texture( void );
	Texture( const char* name , GLuint textureId, GLenum textureNumber );
	virtual ~Texture( void );

	virtual void setTexture( GLuint textureId );
	virtual void setTexture( GLuint textureId, GLenum textureNumber );
	virtual void setTexture( const char* name , GLuint textureId );
	virtual void setTexture( const char* name , GLuint textureId, GLenum textureNumber );

	virtual void bindTexture( void );
};

#endif