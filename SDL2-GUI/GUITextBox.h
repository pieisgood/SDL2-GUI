#ifndef GUITEXTBOX
#define GUITEXTBOX
#include "Element.h"

class GUITextBox : public Element {
private:
	friend class GUIFactory;

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
	virtual void onMouseButton(SDL_Event* ev, GUIEvent* clicked);
};



#endif