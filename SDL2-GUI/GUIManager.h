/**
 * \class GUIManager
 *
 * \ingroup SDL2-GUI
 *
 * \brief Manages all Elements and a seperate framebuffer
 *
 * This class manages the rendering, events and processing 
 * of elements in the element tree. It also manages a seperate 
 * framebuffer so that SDL2-GUI rendering does not interfere
 * with user rendering.
 *
 * \note Needs to be created using a GUIFactory
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

#ifndef SDLGUIMANAGER
#define SDLGUIMANAGER
#include "GUIEvent.h"
#include "Element.h"
#include "GUILayout.h"
#include "GUIButton.h"
#include "GUITextBox.h"
#include <glm\gtc\type_ptr.hpp>
#include <glm\gtx\transform.hpp>


class GUIManager {

private:

	Element* m_window;
	std::map< std::string , Element*> m_idMap;
	ElementSurface m_windowPanel; 
	GLuint m_GUIFrameBuffer; 
	GLuint m_fbTexture; 
	GLuint m_renderBuffer;
	GLuint m_windowVBO;
	GLuint m_windowVTBO;
	GLuint m_windowVAO;
	GLSLProgram* m_panelProgram;
	GUITextBox* m_fps; //a box to render fps with
	GUIView* m_view;
	GUIEvent* m_event;
	Element* m_focus; //element we are currently focused on

public:

	GUIManager( Element* window );

	GUIManager();

	virtual ~GUIManager();

	void draw();
	void onEvent( SDL_Event* event );
	void pollGUIEvent( GUIEvent* in_event );

	void assignWindow( Element* window );
	void assignProgram( GLSLProgram* program );
	void drawFPS();
	void updateMs( float ms ); //we update the ms that have passed since each frame

	Element* getElement( const char* id );

	void assignView( GUIView* view ){
		m_view = view;
	}

	void assignFPS( GUITextBox* fpsBox ){
		m_fps = fpsBox;
	}

	Element* getWindow();

	
};



#endif