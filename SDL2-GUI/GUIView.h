#ifndef GUIVIEW
#define GUIVIEW
#include "GLSLShader.h"
#include<glm\glm.hpp>
#include <stdio.h>
#include <fstream>
#include<map>
#include<string>
#include"GUIFont.h"

//quad surface to render texture over
struct ElementSurface {

	float verts[12];

	float texture_coords[12];

	ElementSurface() {
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

class GUIView {

private:
	GLuint m_vao; 
	GLuint m_vbo; 
	GLuint m_vbot; 
	GLSLProgram* m_program;
	ElementSurface m_surface; //Surface we are rendering to
	GLuint m_errorTexture; //red texture for error checking
	GUIFont* m_font;

public:

	GUIView( GLSLProgram* program );
	virtual ~GUIView();

	void renderPanel( GLuint texture, glm::vec2 position, glm::vec2 scale );
	void renderPanel( GLuint texture, glm::vec2 position, glm::vec2 scale, int subroutine );
	void renderFPS( int ms ); //input milliseconds and render FPS and ms per frame
	void renderText( std::string text , float pos_x, float pos_y, int size );
	void renderText( GLuint textVAO, float pos_x, float pos_y, int size, int numChars );
	void renderTextStash( std::string text , float pos_x, float pos_y, int size );

	void renderError( glm::vec2 position, glm::vec2 scale );

	void prepareRenderer();
	void cleanRenderer();

	void cacheText( std::string text , GLuint vertVBO, GLuint texcoordVBO, GLuint textVAO ){
		m_font->cacheText(text, vertVBO, texcoordVBO, textVAO);
	}

	void updateCachedText( std::string text, GLuint vertVBO, GLuint texcoordVBO, GLuint textVAO, int updateLocation ){
		m_font->updateCacheText(text, vertVBO, texcoordVBO, textVAO, updateLocation, 0 );
	}

	void assignErrorTexture( GLuint texture ){
		m_errorTexture = texture;
	}

	void assignFont( GUIFont* font ){
		m_font = font;
	}


};



#endif