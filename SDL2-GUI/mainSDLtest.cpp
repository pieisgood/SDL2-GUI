#include <iostream>
#include "GUIFactory.h"
#include "GL_Camera.h"
GL_Camera g_cam = GL_Camera();
#include "tut1.h"
#include <SDL.h>
#include <vld.h>

SDL_Window* g_pWindow = 0;
SDL_Renderer* g_pRenderer  = 0;
SDL_GLContext GL_Context = 0;
void CreateOGLContext();


SDLGUI::GUIManager* testGUISystem(SDL_Window* window);

int main(int argc, char **argv){

	CreateOGLContext();
	SDL_Event ourEvents;
	SDLGUI::GUIManager* localManager;
	bool running = true;

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0){
		std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
		return 1;
	}

	g_pWindow = SDL_CreateWindow("SDL2.0 Opengl 3.3 Setup", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);

	GL_Context = SDL_GL_CreateContext(g_pWindow);
	GLenum err = glewInit();

	if(g_pWindow == 0){
		std::cout << "SDL_CreateRenderer error: " << SDL_GetError() << std::endl;
		return 1;
	}


	SDLGUI::GUIFactory* testFactory = new SDLGUI::GUIFactory(g_pWindow);

	std::shared_ptr<SDLGUI::GUIManager> testManager = testFactory->newGUIManager("xmlGUITest.xml");
	

	init();

	int mouseX, mouseY;
	int mouseXRel, mouseYRel;
	const unsigned char* key = SDL_GetKeyboardState(NULL);
	unsigned int mouse = SDL_GetRelativeMouseState(&mouseXRel, &mouseYRel);
	SDL_GetMouseState(&mouseX, &mouseY);
	unsigned int curTime = SDL_GetTicks();
	unsigned int nextTime = 0;
	unsigned int tDelta = 0;
	std::cout << key[SDLK_q];
	std::cout << mouse;
	std::shared_ptr<SDLGUI::GUIEvent> guiEvent(new SDLGUI::GUIEvent());

	int frameCount = 0;
	int msSum = 0;

	while(running){
		SDL_PumpEvents();
		while(SDL_PollEvent(&ourEvents)){
			testManager->onEvent(&ourEvents);
		}
		nextTime = SDL_GetTicks();
		tDelta = nextTime - curTime;
		curTime = nextTime;

		
		if(msSum > 60){
			float fps = (float)frameCount /((float)msSum/1000.0) ;
			testManager->updateMs(fps);
			msSum = 0;
			frameCount = 0;
		}

		testManager->pollGUIEvent(guiEvent);

		if(guiEvent->type == SDLGUI::GUIEventType::GUI_BUTTON){
			printf("you clicked button: %s", guiEvent->button.id);
		}

		if(key[SDL_SCANCODE_A]){
			g_cam.leftMotion(tDelta/100.0);
		}
		if(key[SDL_SCANCODE_W]){
			g_cam.forwardMotion(tDelta/100.0);
		}
		if(key[SDL_SCANCODE_S]){
			g_cam.backwardMotion(tDelta/100.0);
		}
		if(key[SDL_SCANCODE_D]){
			g_cam.rightMotion(tDelta/100.0);
		}
		if(key[SDL_SCANCODE_Q]){
			SDL_Quit();
			running = false;
		}

		if(SDL_GetRelativeMouseState(&mouseXRel, &mouseYRel)&SDL_BUTTON(1) ){
				g_cam.mouseRotation(mouseXRel*2, mouseYRel*2);
			}
		
		testManager->draw();
		display();
		
		
		
		
		
		SDL_GL_SwapWindow(g_pWindow);
		frameCount++;
		msSum += tDelta;
		SDL_Delay(5);
		
	}

	

	return 0;
}


void CreateOGLContext(){
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 16);
}


