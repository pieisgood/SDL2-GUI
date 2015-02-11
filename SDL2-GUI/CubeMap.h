#ifndef CUBE_MAP_TEXTURE
#define CUBE_MAP_TEXTURE
#include"Texture.h"

class CubeMap : public Texture {
private:

public:

	CubeMap( void );
	CubeMap( const char* name , GLuint textureId, GLenum textureNumber );
	virtual ~CubeMap( void );

	virtual void setTexture( GLuint textureId );
	virtual void setTexture( GLuint textureId, GLenum textureNumber );
	virtual void setTexture( const char* name , GLuint textureId );
	virtual void setTexture( const char* name , GLuint textureId, GLenum textureNumber );

	virtual void bindTexture( void );
};

#endif