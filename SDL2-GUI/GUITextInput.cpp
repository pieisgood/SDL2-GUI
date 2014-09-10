#include"GUITextInput.h"

namespace SDLGUI {

void GUITextInput::draw() {
	//m_view->renderText( m_text, m_pos.x, m_pos.y, 10 );
	m_view->renderPanel( m_textureId, m_pos, m_scale );
}

void GUITextInput::onKeyPress( SDL_Event* ev ) {
	//ev->key.
}

}