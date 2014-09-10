

#ifndef GUIEVENT
#define GUIEVENT

namespace SDLGUI {

enum GUIEventType {
	GUI_NONE,
	GUI_BUTTON,
	GUI_LAYOUT
};

typedef struct ButtonEvent {
	const char* id;
	int x;
	int y;
} ButtonEvent;

typedef struct GUIEvent{
	GUIEventType type;
	ButtonEvent button;
} GUIEvent;

}

#endif