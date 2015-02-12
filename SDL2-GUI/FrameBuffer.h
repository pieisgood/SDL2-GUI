#ifndef FRAME_BUFFER_UTILITY
#define FRAME_BUFFER_UTILITY

#include"GLSLShader.h"
#include<memory>

struct FrameBufferSurface {

	float verts[12];

	float texture_coords[12];

	FrameBufferSurface() {
		verts[0] = -1.0;
		verts[1] = 1.0;
		verts[2] = -1.0;
		verts[3] = -1.0;
		verts[4] = 1.0;
		verts[5] = -1.0;
		verts[6] = 1.0;
		verts[7] = -1.0;
		verts[8] = 1.0;
		verts[9] = 1.0;
		verts[10] = -1.0;
		verts[11] = 1.0;

		texture_coords[0] = 0.0;
		texture_coords[1] = 1.0;
		texture_coords[2] = 0.0;
		texture_coords[3] = 0.0;
		texture_coords[4] = 1.0;
		texture_coords[5] = 0.0;
		texture_coords[6] = 1.0;
		texture_coords[7] = 0.0;
		texture_coords[8] = 1.0;
		texture_coords[9] = 1.0;
		texture_coords[10] = 0.0;
		texture_coords[11] = 1.0;
	};

};

class FrameBuffer {
private:
	//data members needed for using a framebuffer
	std::shared_ptr< GLSLProgram > m_program;
	FrameBufferSurface m_windowSurface;
	GLuint m_FBO;
	GLuint m_renderBuffer;
	GLuint m_fbTexture;
	GLuint m_windowVBO;
	GLuint m_windowVTBO;
	GLuint m_windowVAO;


public:
	FrameBuffer( int windowWidth = 800 , int windowHeight = 600 );
	~FrameBuffer( void );
	//this class should allow us to easily create framebuffers and "use" them when rendering 
	//this will allow for easier frame buffer management and switching

	void use( void ); //use this framebuffer for rendering

	void renderToMainBuffer( void ); //renders this framebuffer to the main frame buffer :)

	void setProgram( std::shared_ptr< GLSLProgram > program ) {
		m_program = program;
	}//at some point we need to change this to a material

	GLuint getBufferTexture( void ) {
		return m_fbTexture;
	}

	void setWindow( int windowWidth, int windowHeight );

};

#endif