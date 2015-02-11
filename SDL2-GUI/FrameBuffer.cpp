#include"FrameBuffer.h"

FrameBuffer::FrameBuffer( int windowWidth , int windowHeight ) {

	glGenVertexArrays(1, &m_windowVAO);
	glBindVertexArray(m_windowVAO);

	glGenFramebuffers(1, &m_FBO);
	glGenTextures(1, &m_fbTexture);
	//glActiveTexture (GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_fbTexture);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);

	glTexImage2D(
	  GL_TEXTURE_2D,
	  0,
	  GL_RGBA,
	  windowWidth,
	  windowHeight,
	  0,
	  GL_RGBA,
	  GL_UNSIGNED_BYTE,
	  NULL
	);

	glBindFramebuffer(GL_FRAMEBUFFER, m_FBO);
	glFramebufferTexture2D(
		GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_fbTexture, 0
	);

	glGenRenderbuffers (1, &m_renderBuffer);
	glBindRenderbuffer (GL_RENDERBUFFER, m_renderBuffer);
	glRenderbufferStorage (
		GL_RENDERBUFFER, 
		GL_DEPTH_COMPONENT, 
		windowWidth,
		windowHeight
	);

	glFramebufferRenderbuffer (
		GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_renderBuffer
	);

	GLenum drawBuff[] = { GL_COLOR_ATTACHMENT0 };
	glDrawBuffers(1, drawBuff);

	glGenBuffers(1, &m_windowVBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_windowVBO);
	glBufferData(GL_ARRAY_BUFFER, 2*6*sizeof(float), &m_windowSurface.verts, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

}

FrameBuffer::~FrameBuffer( void ) {

}

void FrameBuffer::use( void ) {

	glBindFramebuffer(GL_FRAMEBUFFER, m_FBO);

}

void FrameBuffer::renderToMainBuffer( void ) {

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glClearColor( 0.46f , 0.53 , 0.6f , 1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glBindVertexArray(m_windowVAO);

	int bufferLoc = glGetUniformLocation( m_program->getHandle() , "panel_texture" );
	
	m_program->use();
		m_program->setUniform("pos", glm::vec2(0, 0));
		m_program->setUniform("scale", glm::vec2(1.0, 1.0));
		m_program->setUniform("sub", 0);
		glActiveTexture(GL_TEXTURE0);
		glUniform1i( bufferLoc , 0 );
		glBindTexture(GL_TEXTURE_2D, m_fbTexture);
		glEnableVertexAttribArray(0);
		glDrawArrays(GL_TRIANGLES, 0, 6);
	glUseProgram(0);

}

