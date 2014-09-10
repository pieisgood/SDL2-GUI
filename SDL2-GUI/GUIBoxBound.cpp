#include"GUIBoxBound.h"

namespace SDLGUI {

GUIBoxBound::GUIBoxBound() {
	m_width = 0;
	m_height = 0;
	m_pos.x = 0;
	m_pos.y = 0;
}

GUIBoxBound::~GUIBoxBound() {

}

bool GUIBoxBound::isHit( float mouse_x, float mouse_y ) {
	if( mouse_x <= (m_pos.x + m_width) && mouse_x >= (m_pos.x) &&
		mouse_y <= (m_pos.y + m_height) && mouse_y >= (m_pos.y)){
			return true;
	}
	return false;
}

void GUIBoxBound::assignWidth( float width ) {
	m_width = width;
}

void GUIBoxBound::assignHeight( float height ) {
	m_height = height;
}

void GUIBoxBound::assignPos( glm::vec2 pos ) {
	m_pos = pos;
}

}