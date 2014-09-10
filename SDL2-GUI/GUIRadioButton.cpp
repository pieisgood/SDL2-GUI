#include"GUIRadioButton.h"

namespace SDLGUI {

GUIRadioButton::GUIRadioButton(): m_state(false) {}

GUIRadioButton::~GUIRadioButton(){}

void GUIRadioButton::draw() {

}

void GUIRadioButton::onMouseButton( SDL_Event* ev, std::shared_ptr<GUIEvent> clicked ) {
	if( this->isOver( ev->button.x, ev->button.y ) ){
		m_state = !m_state;
	}

}

void GUIRadioButton::onClick(){}

bool GUIRadioButton::isOver(int x, int y ) { return false; }

void GUIRadioButton::onMouseMotion( SDL_Event* ev ) {}

}