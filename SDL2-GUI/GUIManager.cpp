#include"GUIManager.h"
#include<iostream>

namespace SDLGUI {

GUIManager::GUIManager(){
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

	glBindFramebuffer(GL_FRAMEBUFFER, m_GUIFrameBuffer);
	
		glClearColor(1.0f, 1.0f,1.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		m_view->prepareRenderer();
		m_window->draw();
		this->drawFPS();

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glBindVertexArray(m_windowVAO);
	
		m_panelProgram->use();
			m_panelProgram->setUniform("pos", glm::vec2(0, 0));
			m_panelProgram->setUniform("scale", glm::vec2(1.0, 1.0));
			m_panelProgram->setUniform("sub", 0);
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, m_fbTexture);
			glEnableVertexAttribArray(0);
			glBindBuffer(GL_ARRAY_BUFFER, m_windowVBO);
				glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
			glDrawArrays(GL_TRIANGLES, 0, 6);
		glUseProgram(0);

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
}

void GUIManager::assignWindow(std::shared_ptr<Element> window){
	glGenVertexArrays(1, &m_windowVAO);
	glBindVertexArray(m_windowVAO);
	m_window = window;
	glGenFramebuffers(1, &m_GUIFrameBuffer);
	glGenTextures(1, &m_fbTexture);
	glActiveTexture (GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_fbTexture);
	glTexImage2D(
	  GL_TEXTURE_2D,
	  0,
	  GL_RGBA,
	  m_window->getWidth(),
	  m_window->getHeight(),
	  0,
	  GL_RGBA,
	  GL_UNSIGNED_BYTE,
	  NULL
	);

	glBindFramebuffer(GL_FRAMEBUFFER, m_GUIFrameBuffer);
	glFramebufferTexture2D(
		GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_fbTexture, 0
	);

	glGenRenderbuffers (1, &m_renderBuffer);
	glBindRenderbuffer (GL_RENDERBUFFER, m_renderBuffer);
	glRenderbufferStorage (
		GL_RENDERBUFFER, 
		GL_DEPTH_COMPONENT, 
		m_window->getWidth(),
	    m_window->getHeight()
	);

	glFramebufferRenderbuffer (
		GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_renderBuffer
	);

	GLenum drawBuff[] = { GL_COLOR_ATTACHMENT0 };
	glDrawBuffers(1, drawBuff);

	glGenBuffers(1, &m_windowVBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_windowVBO);
	glBufferData(GL_ARRAY_BUFFER, 2*6*sizeof(float), &m_windowPanel.verts, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

GUIManager::~GUIManager(){

}

}