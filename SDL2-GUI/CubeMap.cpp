#include"CubeMap.h"


CubeMap::CubeMap( void ) {
	Texture::Texture();
}

CubeMap::CubeMap( const char* name , GLuint textureId, GLenum textureNumber ) 
{
	Texture::Texture( name , textureId , textureNumber );
}

CubeMap::~CubeMap( void ) {

}

void CubeMap::setTexture( GLuint textureId ) {

	m_texId = textureId;

}

void CubeMap::setTexture( GLuint textureId, GLenum textureNumber ) {

	m_texId = textureId;
	m_texNum = textureNumber;

}

void CubeMap::setTexture( const char* name , GLuint textureId ) {

	m_name = name;
	m_texId = textureId;

}

void CubeMap::setTexture( const char* name , GLuint textureId, GLenum textureNumber ) {

	m_name = name;
	m_texId = textureId;
	m_texNum = textureNumber;

}

void CubeMap::bindTexture( void ) {

	glActiveTexture( m_texNum );
	glBindTexture( GL_TEXTURE_CUBE_MAP , m_texId );

}