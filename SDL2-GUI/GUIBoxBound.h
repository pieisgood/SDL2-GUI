#ifndef GUIBOXBOUND
#define GUIBOXBOUND
#include "GUIBound.h"

class GUIBoxBound : public GUIBound {
private:
	float m_width;
	float m_height;
	glm::vec2 m_pos; //top left hand point

public:
	GUIBoxBound();
	virtual ~GUIBoxBound();

	virtual bool isHit(float mouse_x, float mouse_y);
	void assignWidth(float width);
	void assignHeight(float height);
	void assignPos(glm::vec2 pos);
};



#endif