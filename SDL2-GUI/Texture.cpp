#include"Texture.h"

Texture::Texture( void ) {}
Texture::Texture( const char* name, GLuint textureId , GLenum textureNumber = GL_TEXTURE0 ) :
	m_name( name ) , m_texId( textureId ) , m_texNum( textureNumber )
{}

Texture::~Texture( void ) {

	//delete( m_name );

}

void Texture::setTexture( GLuint textureId ) {

	m_texId = textureId;

}

void Texture::setTexture( GLuint textureId, GLenum textureNumber ) {

	m_texId = textureId;
	m_texNum = textureNumber;

}

void Texture::setTexture( const char* name , GLuint textureId ) {

	m_name = name;
	m_texId = textureId;

}

void Texture::setTexture( const char* name , GLuint textureId, GLenum textureNumber ) {

	m_name = name;
	m_texId = textureId;
	m_texNum = textureNumber;

}

void Texture::bindTexture( void ) {

	glActiveTexture( m_texNum );
	glBindTexture( GL_TEXTURE_2D , m_texId );

}