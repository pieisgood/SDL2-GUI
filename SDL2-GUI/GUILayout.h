/**
 * \class GUILayout
 *
 * \ingroup SDL2-GUI
 *
 * \brief Should work like an HTML div tag
 *
 * This class should provide the ability to 
 * have relative placement of elements within
 * certain boundaries. Like a sub window.
 * 
 *
 * \note Needs to better defined
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

#ifndef GUILAYOUT
#define GUILAYOUT
#include "Element.h"


namespace SDLGUI {

class GUILayout : public Element {
private:
	friend class GUIFactory;
	std::shared_ptr<GUIView> m_view;

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

	void assignView( std::shared_ptr<GUIView> view ){
		m_view = view;
	}

public:

	GUILayout();
	virtual ~GUILayout();

	virtual void draw();
	virtual void onClick();
	virtual bool isOver(int x, int y);
	virtual void onMouseMotion(SDL_Event* ev);
	virtual void onMouseButton(SDL_Event* ev, std::shared_ptr<GUIEvent> clicked);
	virtual void onMouseScroll( SDL_Event* ev );
};

}

#endif