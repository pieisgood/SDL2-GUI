#ifndef GUIBOUND
#define GUIBOUND
#include <glm\glm.hpp>

class GUIBound {

public:
	GUIBound(){};
	virtual ~GUIBound(){};

	virtual bool isHit( float mouse_x, float mouse_y ) = 0;

};

#endif