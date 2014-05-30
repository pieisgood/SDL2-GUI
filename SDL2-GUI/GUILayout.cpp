#include"GUILayout.h"

GUILayout::GUILayout(){
	m_pos.x = 0;
	m_pos.y = 0;
	m_width = 0;
	m_height = 0;
}

GUILayout::~GUILayout(){

}

void GUILayout::draw(){
	//optional layout render goes here

	std::vector<Element*>::iterator itr;
	itr = m_children.begin();

	for(; itr != m_children.end(); itr++){
		itr[0]->draw();
	}
}

bool GUILayout::isOver(int x, int y){
	if( y > (m_screenPos.y) && y < (m_screenPos.y + m_height) &&
		x > (m_screenPos.x) && x < (m_screenPos.x + m_width) ){
			return true;
	}
	return false;
}

void GUILayout::onClick(){
	std::vector<Element*>::iterator itr;
	itr = m_children.begin();

	for(; itr != m_children.end(); itr++){
		itr[0]->onClick();
	}
}

void GUILayout::onMouseMotion(SDL_Event* ev){
	if( !( this->isOver( ev->motion.x, ev->motion.y ) ) ) {
		return;
	}

	std::vector<Element*>::iterator itr;
	itr = m_children.begin();

	for(; itr != m_children.end(); itr++){
		itr[0]->onMouseMotion(ev);
	}
}

void GUILayout::onMouseButton(SDL_Event* ev, GUIEvent* clicked){
	if( !(this->isOver(ev->button.x, ev->button.y)) ){
		return;
	}

	std::vector<Element*>::iterator itr;
	itr = m_children.begin();

	for(; itr != m_children.end(); itr++){
		itr[0]->onMouseButton(ev, clicked);
	}
}