#include"GUIButton.h"

GUI2DButton::GUI2DButton(){
	m_id = "";
}

GUI2DButton::~GUI2DButton(){

}

bool GUI2DButton::isOver(int x, int y){
	if( y > (m_screenPos.y) && y < (m_screenPos.y + m_height) &&
		x > (m_screenPos.x) && x < (m_screenPos.x + m_width) ){
			return true;
	}
	return false;
}

void GUI2DButton::draw(){
	m_view->renderPanel(m_textureId, m_pos, m_scale, m_subRoutine);
}

void GUI2DButton::onClick(){
	
}

void GUI2DButton::onMouseMotion(SDL_Event* ev){

	//Highlight if mouse is over button
	if( this->isOver(ev->motion.x , ev->motion.y) ){
		m_subRoutine = 1;
	}
	else{
		m_subRoutine = 0;
		return;
	}

	//iterate over children
	std::vector<Element*>::iterator itr;
	itr = m_children.begin();

	for(; itr != m_children.end(); itr++){
		itr[0]->onMouseMotion(ev);
	}
}

void GUI2DButton::onMouseButton(SDL_Event* ev, GUIEvent* clicked){

	bool over = this->isOver(ev->button.x , ev->button.y) ;

	if( ev->type == SDL_MOUSEBUTTONDOWN){
		if( over ){
			m_subRoutine = 2;
			clicked->type = GUIEventType::GUI_BUTTON;
			clicked->button.id = m_id;
			clicked->button.x = m_pos.x;
			clicked->button.y = m_pos.y;
			this->onClick();
		}
	}
	else if(over){
		m_subRoutine = 1;
	}
	else{
		m_subRoutine = 0;
		return;
	}

	//iterate over children
	std::vector<Element*>::iterator itr;
	itr = m_children.begin();

	for(; itr != m_children.end(); itr++){
		itr[0]->onMouseButton(ev, clicked);
	}

}