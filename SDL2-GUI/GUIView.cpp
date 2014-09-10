#include"GUIView.h"

namespace SDLGUI {

GUIView::GUIView( std::shared_ptr<GLSLProgram> program){
	//accept compiled GLSL program
	m_program = program;
	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);

	m_program->use();

	//generate VBO to hold surface data
	glGenBuffers(1, &m_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(m_surface.verts), m_surface.verts, GL_STATIC_DRAW);

	//bind vertex position attribute to GLSL program
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, NULL);
	m_program->bindAttribLocation(0, "vertex_position");
	glEnableVertexAttribArray(0);
		
}

GUIView::~GUIView(){

}

void GUIView::renderPanel( GLuint texture, glm::vec2 position, glm::vec2 scale ){
	glBindTexture(GL_TEXTURE_2D, texture);
	m_program->setUniform("pos", position);
	m_program->setUniform("scale", scale);
	m_program->setUniform("sub", 0);
	glDrawArrays(GL_TRIANGLES, 0, 6);
}

void GUIView::renderPanel( GLuint texture, glm::vec2 position, glm::vec2 scale, int subroutine ){
	glBindTexture(GL_TEXTURE_2D, texture);
	m_program->setUniform("pos", position);
	m_program->setUniform("scale", scale);
	m_program->setUniform("sub" , subroutine);
	glDrawArrays(GL_TRIANGLES, 0, 6);
}

void GUIView::renderText( GLuint textVAO, float pos_x, float pos_y, int size, int numChars ) {
	m_font->renderText( textVAO, pos_x, pos_y, size, numChars );
}

void GUIView::renderError( glm::vec2 position, glm::vec2 scale ){
	glBindTexture(GL_TEXTURE_2D, m_errorTexture);
	m_program->setUniform("pos", position);
	m_program->setUniform("scale", scale);
	m_program->setUniform("sub", 0);
	glDrawArrays(GL_TRIANGLES, 0, 6);
}

void GUIView::prepareRenderer(){
	m_program->use();
	glBindVertexArray(m_vao);
	glEnableVertexAttribArray(0);
}

void GUIView::cleanRenderer(){
	glUseProgram(0);
}

}