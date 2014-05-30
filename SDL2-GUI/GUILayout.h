#ifndef GUILAYOUT
#define GUILAYOUT
#include "Element.h"

class GUILayout : public Element {
private:
	friend class GUIFactory;
	GUIView* m_view;

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

	void assignView( GUIView* view ){
		m_view = view;
	}

public:

	GUILayout();
	virtual ~GUILayout();

	virtual void draw();
	virtual void onClick();
	virtual bool isOver(int x, int y);
	virtual void onMouseMotion(SDL_Event* ev);
	virtual void onMouseButton(SDL_Event* ev, GUIEvent* clicked);
};


#endif