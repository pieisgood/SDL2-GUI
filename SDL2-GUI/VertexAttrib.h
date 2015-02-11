#ifndef GLSL_VERTEX_ATTRIBUTE
#define GLSL_VERTEX_ATTRIBUTE

#include<gl\glew.h>

class VertexAttrib {
private:
	const char* m_name;
	GLuint m_vbo; //the buffer object holding our data, use this to delete the data later
	GLuint m_AttributeNum; //the layout number of the attribute

public:
	VertexAttrib( void );
	VertexAttrib( char* name );
	VertexAttrib( char* name, GLuint num );
	virtual ~VertexAttrib( void );

	//some virtual functions for working with VertexAttributes here.

	void bindAttrib( void );

	GLuint getLocation( void );
	const char* getName( void );

	void setName( const char* name );
	void setVBO( GLuint vbo );
	void setAttributeNum( GLuint num );

};


#endif