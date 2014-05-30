#ifndef GUITEXTINPUT
#define GUITEXTINPUT
#include"Element.h"

class GUITextInput : public Element {

private:
	GLuint m_subRoutine; //the shader subroutine we will use for the button
	GLuint m_textureId; //the texture we will use for this button

public:

	virtual void draw();
	virtual void onClick();
	virtual bool isOver( int x, int y );
	virtual void onMouseMotion( SDL_Event* ev );
	virtual void onMouseButton( SDL_Event* ev, GUIEvent* clicked );
	virtual void onKeyPress( SDL_Event* ev );
	virtual void addChild( Element* child ){};
	virtual void addBound( GUIBound* bound );
	virtual void addParent( Element* parent );
	virtual void assignLayer( unsigned int layer );
	virtual void assignProgram( GLSLProgram* program );


};

#endif