/**
 * \class GUITextBox
 *
 * \ingroup SDL2-GUI
 *
 * \brief A text box for word wrapping
 *
 * Allows for word wrapping and aligned text input.
 * 
 * 
 * 
 *
 * \note Should be used for all static text
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

#ifndef GUITEXTBOX
#define GUITEXTBOX
#include "Element.h"

namespace SDLGUI {

class GUITextBox : public Element {
private:
	friend class GUIFactory;
	glm::vec2 m_textPos;

protected:

	void assignWidth(float width){
		m_width = width;
	}

	void assignHeight(float height){
		m_height = height;
	}

	void assignPosition(glm::vec2 pos){
		m_pos = pos;
	}

	void assignScale( glm::vec2 scale ){
		m_scale = scale;
	}


public:

	GUITextBox();
	virtual ~GUITextBox();

	virtual void draw();
	virtual void onClick();
	virtual bool isOver(int x, int y);
	virtual void onMouseMotion(SDL_Event* ev);
	virtual void onMouseButton(SDL_Event* ev, std::shared_ptr<GUIEvent> clicked);
	virtual void onMouseScroll(SDL_Event* ev);
};

}

#endif