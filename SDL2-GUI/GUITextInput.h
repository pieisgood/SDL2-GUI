/**
 * \class GUITextInput
 *
 * \ingroup SDL2-GUI
 *
 * \brief Dynamic text input
 *
 * Recieves user text input and builds a string.
 * Also renders the string to the screen.
 * 
 * 
 *
 * \note Should be used for user text input
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

#ifndef GUITEXTINPUT
#define GUITEXTINPUT
#include <memory>
#include"Element.h"

namespace SDLGUI {

class GUITextInput : public Element {

private:
	GLuint m_subRoutine; //the shader subroutine we will use for the button
	GLuint m_textureId; //the texture we will use for this button

public:

	virtual void draw();
	virtual void onClick();
	virtual bool isOver( int x, int y );
	virtual void onMouseMotion( SDL_Event* ev );
	virtual void onMouseButton( SDL_Event* ev, std::shared_ptr<GUIEvent> clicked );
	virtual void onKeyPress( SDL_Event* ev );
	virtual void addChild( std::shared_ptr<Element> child ){};
	virtual void addBound( std::shared_ptr<GUIBound> bound );
	virtual void addParent( std::shared_ptr<Element> parent );
	virtual void assignLayer( unsigned int layer );
	virtual void assignProgram( std::shared_ptr<GLSLProgram> program );


};

}

#endif