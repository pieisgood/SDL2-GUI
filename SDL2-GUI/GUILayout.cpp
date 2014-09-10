#include"GUILayout.h"
#include<iostream>

namespace SDLGUI {

GUILayout::GUILayout()
	: Element(){

}

GUILayout::~GUILayout(){

}

void GUILayout::draw(){
	//optional layout render goes here
	//m_view->renderError(m_pos, m_scale);

	std::vector<std::shared_ptr<Element>>::iterator itr;
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
	std::vector<std::shared_ptr<Element>>::iterator itr;
	itr = m_children.begin();

	for(; itr != m_children.end(); itr++){
		itr[0]->onClick();
	}
}

void GUILayout::onMouseMotion(SDL_Event* ev){
	if( !( this->isOver( ev->motion.x, ev->motion.y ) ) ) {
		return;
	}

	std::vector<std::shared_ptr<Element>>::iterator itr;
	itr = m_children.begin();

	for(; itr != m_children.end(); itr++){
		itr[0]->onMouseMotion(ev);
	}
}

void GUILayout::onMouseButton(SDL_Event* ev, std::shared_ptr<GUIEvent> clicked){
	if( !(this->isOver(ev->button.x, ev->button.y)) ){
		return;
	}

	std::vector<std::shared_ptr<Element>>::iterator itr;
	itr = m_children.begin();

	for(; itr != m_children.end(); itr++){
		itr[0]->onMouseButton(ev, clicked);
	}
}

void GUILayout::onMouseScroll( SDL_Event* ev ) {

	m_pos.y += ev->wheel.y;
	m_screenPos.y -= ev->wheel.y*240;

	std::vector<std::shared_ptr<Element>>::iterator itr;
	itr = m_children.begin();

	for(; itr != m_children.end(); itr++){
		itr[0]->onMouseScroll(ev);
	}
}

}