#include"GUIManager.h"
#include<iostream>

namespace SDLGUI {

GUIManager::GUIManager(){
	m_GUIFrameBuffer = std::shared_ptr<FrameBuffer>( new FrameBuffer() );
	m_event = std::shared_ptr<GUIEvent>(new GUIEvent());
	m_event->type = GUI_NONE;
}

GUIManager::GUIManager(std::shared_ptr<Element> window){
	assignWindow(window);
}

void GUIManager::pollGUIEvent(std::shared_ptr<GUIEvent> in_event){
	//possible problems with this code
	*in_event = *m_event;
	m_event = std::shared_ptr<GUIEvent> (new GUIEvent());
	m_event->type = GUI_NONE;
}

void GUIManager::updateMs(float ms){
	std::string text = std::string("FPS: ");
	text.append(std::to_string((int)ms));
	m_fps->updateText(text, 0);
}

void GUIManager::drawFPS(){
	m_fps->draw();
}

void GUIManager::draw(){

	m_GUIFrameBuffer->use();
	
		glClearColor(1.0f, 1.0f,1.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		m_view->prepareRenderer();
		m_window->draw();

	m_GUIFrameBuffer->renderToMainBuffer();

}

void GUIManager::onEvent(SDL_Event* event){
	//handle SDL events and send to children
	if(event->type == SDL_MOUSEMOTION){
		m_window->onMouseMotion(event);
	}
	else if(event->type == SDL_MOUSEBUTTONDOWN || event->type == SDL_MOUSEBUTTONUP){
		m_window->onMouseButton(event, m_event);
	}
	else if(event->type == SDL_MOUSEWHEEL){
		m_window->onMouseScroll(event);
		std::cout << event->wheel.y << '\n';
	}
}

void GUIManager::assignProgram(std::shared_ptr<GLSLProgram> program){
	m_panelProgram = program;
	m_GUIFrameBuffer->setProgram( m_panelProgram );
}

void GUIManager::assignWindow(std::shared_ptr<Element> window){
	m_window = window;
	m_GUIFrameBuffer->setWindow( window->getWidth(), window->getHeight() );
}

GUIManager::~GUIManager(){

}

}