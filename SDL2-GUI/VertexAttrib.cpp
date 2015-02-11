#include"VertexAttrib.h"

VertexAttrib::VertexAttrib( void ) {}
VertexAttrib::VertexAttrib( char* name ) : m_name( name ) {}
VertexAttrib::VertexAttrib( char* name, GLuint num ) :
	m_name( name ) , m_AttributeNum( num ) {}

VertexAttrib::~VertexAttrib( void ) {}

void VertexAttrib::bindAttrib( void ) {

	//glEnableVertexAttribArray( m_AttributeNum );

}

GLuint VertexAttrib::getLocation( void ) {

	return m_AttributeNum;

}

const char* VertexAttrib::getName( void ) {

	return m_name;

}

void VertexAttrib::setName( const char* name ) {

	m_name = name;

}

void VertexAttrib::setVBO( GLuint vbo ) {

	m_vbo = vbo;

}

void VertexAttrib::setAttributeNum( GLuint num ) {

	m_AttributeNum = num;

}