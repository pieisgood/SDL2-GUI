/// \defgroup SDL2-GUI
/**
 * \class Element
 *
 * \ingroup SDL2-GUI
 *
 * \brief Base class for all HTML elements
 *
 * This class is the base class for all HTML Elements.
 * Elements build a tree by have a list of children.
 * Each element draw call must also draw its children.
 * 
 *
 * \note All elements must derive from this class
 *
 * \author  Lee Jacobs 
 *
 * \version  1.0 
 *
 * \date 2014/06/10 
 *
 * Contact: leemichaeljacobs@gmail.com
 *
 * Created on: 2014/05/28
 *
 * $Id: doxygen-howto.html,v 1.5 2005/04/14 14:16:20 bv Exp $
 *
 */

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

//This BoxModel represents HTML CSS box model formatting
struct BoxModel {
	glm::vec4 margin;
	glm::vec4 border;
	glm::vec4 padding;
	glm::vec4 content;
};


class Element {

protected:

	Element* m_parent; /*!< The parent Element to this Element */
	GUIView* m_view; /*!< A view object to render this Element */
	GUIBound* m_boundary; //a boundary to test hits on
	GLuint m_elementVAO;
	GLuint m_textVAO; /*!< Vertex Array Object to handle Text geometry and UV-Coords */
	GLuint m_textVBOVerts; /*!< Vertex Buffer Object to hold text vertex data */
	GLuint m_textVBOTexCoords; /*!< Vertex Buffer Object to hold text UV-coord data */
	glm::vec2 m_pos;
	glm::vec2 m_screenPos;
	glm::vec2 m_scale;
	glm::vec4 m_stencilRect; /*!< A rectangle used to define where to draw elements */
	std::string m_text;
	float m_width;
	float m_height;
	unsigned int m_textChars; //number of characters in this elements text
	unsigned int m_layer; //layer to draw Element on
	std::vector<Element* > m_children; //every element can have children
	
public:

	/*!
	 * \brief builds an Elment with empty or zero intial conditions
	 */
	Element():m_pos(glm::vec2(0.0,0.0)),m_screenPos(glm::vec2(0.0,0.0)), m_scale(glm::vec2(1.0,1.0)), 
		m_stencilRect(glm::vec4(1.0)), m_text(""), m_width(0), m_height(0),m_textChars(0), m_parent(NULL),
		m_view(NULL), m_layer(0) {

		glGenVertexArrays(1, &m_textVAO);
		glGenBuffers( 1, &m_textVBOVerts);
		glGenBuffers( 1, &m_textVBOTexCoords);
	}

	/*!
	 * \brief Deletes all pointers and children elements of this element
	 */
	virtual ~Element();

	/*!
	 * \brief should be over ridden to draw an element properly
	 */
	virtual void draw() = 0;

	/*!
	 * \brief May need to be deleted as it serves not really a purpose
	 */
	virtual void onClick() = 0;

	/*!
	 * \brief Used to check whether the mouse is over the current element
	 *
	 * \param x The x position of the mouse
	 * \param y The y position of the mouse
	 *
	 * \return True if the mouse is over the element, false otherwise.
	 */
	virtual bool isOver( int x, int y ) = 0;

	/*!
	 * \brief Handles mouse motions, should be overridden
	 *
	 * \param ev An sdl_event that should be a mouse motion event
	 *
	 */
	virtual void onMouseMotion( SDL_Event* ev ) = 0;

	/*!
	 * \brief Handles mouse button clicked events
	 *
	 * \param ev An sdl_event that should be a mouse button event
	 * \param clicked A GUIEvent reference that will be filled in when the GUIManager handles a button event
	 */
	virtual void onMouseButton( SDL_Event* ev, GUIEvent* clicked ) = 0;

	/*!
	 * \brief Handles mouse scroll event, should be overriden
	 *
	 * \param ev An sdl_event should be a scroll event
	 *
	 */
	virtual void onMouseScroll( SDL_Event* ev ) {};

	/*!
	 * \brief Handles a KeyPress event, should be overriden
	 *
	 * \param ev An sdl_event that should be a KeyPress event
	 *
	 */
	virtual void onKeyPress( SDL_Event* ev ) {};

	/*!
	 * \brief This function appends the child element to the children list in the current element
	 *
	 * \param child The child element to add to the child element list
	 *
	 */
	virtual void addChild( Element* child );

	/*!
	 * \brief add a bound to the element
	 *
	 * \param bound A GUIBound to add to the element
	 */
	virtual void addBound( GUIBound* bound );

	/*!
	 * \brief add a parent element to this element
	 *
	 * \param parent A parent element to add to this element
	 */
	virtual void addParent( Element* parent );


	/*!
	 * \brief
	 *
	 * \param
	 *
	 * \return
	 */
	virtual void assignView( GUIView* view ) {
		m_view = view;
	}

	/*!
	 * \brief
	 *
	 * \param
	 *
	 * \return
	 */
	virtual unsigned int getWidth() {
		return m_width;
	}

	/*!
	 * \brief
	 *
	 * \param
	 *
	 * \return
	 */
	virtual unsigned int getHeight() {
		return m_height;
	}

	/*!
	 * \brief
	 *
	 * \param
	 *
	 * \return
	 */
	virtual void assignScreenPosition( float x, float y ) {
		m_screenPos.x = x;
		m_screenPos.y = y;
	}

	/*!
	 * \brief
	 *
	 * \param
	 *
	 * \return
	 */
	void assignText( std::string text ) {
		m_text = text;
		m_view->cacheText( text, m_textVBOVerts, m_textVBOTexCoords, m_textVAO );
	}

	/*!
	 * \brief
	 *
	 * \param
	 *
	 * \return
	 */
	void assignNumChars( unsigned int numChars ){
		m_textChars = numChars;
	}

	/*!
	 * \brief
	 *
	 * \param
	 *
	 * \return
	 */
	void updateText( std::string text, int updateLocation ) {
		m_text = text;
		m_view->updateCachedText( text, m_textVBOVerts, m_textVBOTexCoords, m_textVAO, updateLocation );
	};

	/*!
	 * \brief
	 *
	 * \param
	 *
	 * \return
	 */
	void assignTextWrap(std::string text, int width){
		m_text = text;
		m_view->cacheTextWrap(text, m_textVBOVerts,  m_textVBOTexCoords, m_textVAO, width );
	}

	/*!
	 * \brief
	 *
	 * \param
	 *
	 * \return
	 */
	void assignStencil( glm::vec4 stencil ) {
		m_stencilRect = stencil;
	}

};






#endif