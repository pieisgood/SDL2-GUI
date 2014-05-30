#ifndef SDLGUIELEMENT
#define SDLGUIELEMENT
#include <SDL.h>
#include <vector>
#include "GUIEvent.h"
#include "GUIBound.h"
#include "GUIView.h"
#include <GL\glew.h>
#include <glm\glm.hpp>

enum {
	LEFT = 0,
	RIGHT,
	TOP,
	BOTTOM,
	CENTER,
	CENTER_LEFT,
	CENTER_RIGHT,
	CENTER_TOP,
	CENTER_BOTTOM
};


class Element {

protected:

	Element* m_parent; //parent of this child element
	GUIView* m_view;
	GUIBound* m_boundary; //a boundary to test hits on
	GLuint m_elementVAO;
	GLuint m_textVAO;
	GLuint m_textVBOVerts;
	GLuint m_textVBOTexCoords;
	glm::vec2 m_pos;
	glm::vec2 m_screenPos;
	glm::vec2 m_scale;
	glm::vec4 m_stencilRect; // a rectangle that represents the area of which to draw on
	std::string m_text;
	float m_width;
	float m_height;
	unsigned int m_textChars; //number of characters in this elements text
	unsigned int m_layer; //layer to draw Element on
	std::vector<Element* > m_children; //every element can have children
	
public:

	Element():m_pos(glm::vec2(0.0,0.0)),m_screenPos(glm::vec2(0.0,0.0)), m_scale(glm::vec2(1.0,1.0)), 
		m_stencilRect(), m_text(""), m_width(0), m_height(0),m_textChars(0), m_parent(NULL),
		m_view(NULL), m_layer(0) {

		glGenVertexArrays(1, &m_textVAO);
		glGenBuffers( 1, &m_textVBOVerts);
		glGenBuffers( 1, &m_textVBOTexCoords);
	}

	virtual ~Element();

	virtual void draw() = 0;
	virtual void onClick() = 0;
	virtual bool isOver( int x, int y ) = 0;
	virtual void onMouseMotion( SDL_Event* ev ) = 0;
	virtual void onMouseButton( SDL_Event* ev, GUIEvent* clicked ) = 0;
	virtual void onMouseScroll( SDL_Event* ev ) {};
	virtual void onKeyPress( SDL_Event* ev ) {};
	virtual void addChild( Element* child );
	virtual void addBound( GUIBound* bound );
	virtual void addParent( Element* parent );
	virtual void assignLayer( unsigned int layer );

	virtual void assignView( GUIView* view ) {
		m_view = view;
	}

	virtual unsigned int getWidth() {
		return m_width;
	}

	virtual unsigned int getHeight() {
		return m_height;
	}

	virtual void assignScreenPosition( float x, float y ) {
		m_screenPos.x = x;
		m_screenPos.y = y;
	}

	void assignText( std::string text ) {
		m_text = text;
		m_view->cacheText( text, m_textVBOVerts, m_textVBOTexCoords, m_textVAO );
	}

	void assignNumChars( unsigned int numChars ){
		m_textChars = numChars;
	}

	void updateText( std::string text, int updateLocation ) {
		m_text = text;
		m_view->updateCachedText( text, m_textVBOVerts, m_textVBOTexCoords, m_textVAO, updateLocation );
	};

};






#endif