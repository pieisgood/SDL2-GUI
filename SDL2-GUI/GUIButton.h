#ifndef SDLGUIBUTTON
#define SDLGUIBUTTON
#include "Element.h"
#include <glm\glm.hpp>

class GUI2DButton : public Element {
private:
	friend class GUIFactory;

	const char* m_id;
	GLuint m_subRoutine; //the shader subroutine we will use for the button
	GLuint m_textureId; //the texture we will use for this button


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

	void assignId(const char* id){
		m_id = id;
	}

	void assignTexture(GLuint textureId){
		m_textureId = textureId;
	}

	void assignScale( glm::vec2 scale) {
		m_scale = scale;
	}

public:
	GUI2DButton();
	virtual ~GUI2DButton();

	virtual void draw();
	virtual void onClick();
	virtual bool isOver(int x, int y);
	virtual void onMouseMotion(SDL_Event* ev);
	virtual void onMouseButton(SDL_Event* ev, GUIEvent* clicked);

};



#endif