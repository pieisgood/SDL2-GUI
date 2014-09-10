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

namespace SDLGUI {

class GUIManager {

private:

	std::shared_ptr<Element> m_window;
	std::map< std::string , std::shared_ptr<Element>> m_idMap;
	ElementSurface m_windowPanel; 
	GLuint m_GUIFrameBuffer; 
	GLuint m_fbTexture; 
	GLuint m_renderBuffer;
	GLuint m_windowVBO;
	GLuint m_windowVTBO;
	GLuint m_windowVAO;
	std::shared_ptr<GLSLProgram> m_panelProgram;
	std::shared_ptr<GUITextBox> m_fps; //a box to render fps with
	std::shared_ptr<GUIView> m_view;
	std::shared_ptr<GUIEvent> m_event;
	std::shared_ptr<Element> m_focus; //element we are currently focused on

public:

	GUIManager( std::shared_ptr<Element> window );

	GUIManager();

	virtual ~GUIManager();

	void draw();
	void onEvent( SDL_Event* event );
	void pollGUIEvent( std::shared_ptr<GUIEvent> in_event );

	void assignWindow( std::shared_ptr<Element> window );
	void assignProgram( std::shared_ptr<GLSLProgram> program );
	void drawFPS();
	void updateMs( float ms ); //we update the ms that have passed since each frame

	Element* getElement( const char* id );

	void assignView( std::shared_ptr<GUIView> view ){
		m_view = view;
	}

	void assignFPS( std::shared_ptr<GUITextBox> fpsBox ){
		m_fps = fpsBox;
	}

	std::shared_ptr<Element> getWindow();

	
};

}

#endif