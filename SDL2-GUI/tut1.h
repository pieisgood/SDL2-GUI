//Copyright (C) 2010-2012 by Jason L. McKesson
//This file is licensed under the MIT License.

#ifndef TUTORIAL
#define TUTORIAL

//#define GLEW_STATIC
#include <fstream>
#include <algorithm>
#include <GL/glew.h>
#include <glm\gtc\type_ptr.hpp>
#include <glm\gtx\transform.hpp>
#include "UtilityFuncs.h"
#include "GLSLShader.h"
#include <string>
#include <vector>
#include <stdio.h>

glm::mat4 lookAt(glm::vec4 camera_pos, glm::vec4 target_pos, glm::vec3 up_dir); //implement to produce a matrix that looks at a position

GLuint theProgram;
GLuint panelProgram;
GLSLProgram *testProgram;
GLSLProgram *mProgram;

const char* strVertexShader = "tri.vert";

const char* strFragmentShader = "tri.frag";

void InitializeProgram()
{

	mProgram = new GLSLProgram();
	mProgram->compileShaderFromFile("tri.vert", GLSLShader::VERTEX);
	mProgram->compileShaderFromFile("tri.frag", GLSLShader::FRAGMENT);
	mProgram->link();

	loadMesh("monkey.dae");
}

const float vertexPositions[] = {
     0.0f,    0.5f, -1.0f, 1.0f,
     0.5f, -0.366f, -1.5f, 1.0f,
    -0.5f, -0.366f, -0.2f, 1.0f,
     1.0f,    0.0f, 0.0f, 1.0f,
     0.0f,    1.0f, 0.0f, 1.0f,
     0.0f,    0.0f, 1.0f, 1.0f,
};
float matrixTransform[] = {
  1.0f, 0.0f, 0.0f, 0.0f, // first column
  0.0f, 1.0f, 0.0f, 0.0f, // second column
  0.0f, 0.0f, 1.0f, 0.0f, // third column
  0.5f, 0.0f, 0.0f, 1.0f // fourth column
};
float points[] = {
  -1.0,  1.0,
  -1.0, -1.0,
   1.0, -1.0,
   1.0, -1.0,
   1.0,  1.0,
  -1.0,  1.0
};

float tex_coords[] = {
  0.0, 1.0,
  0.0, 0.0,
  1.0, 0.0,
  1.0, 0.0,
  1.0, 1.0,
  0.0, 1.0
};

GLuint positionBufferObject;
GLuint vao;
GLuint panelVao;
GLuint offsetUniform;
GLuint perspectiveMatrixUnif;
GLuint vertBuffer;
GLuint texcBuffer;
GLuint transform;
GLuint viewMatrix;
GLuint normBuffer;
GLuint panMatrix;
GLuint texUni;
GLuint subThing;
GLuint otherThing;
float theMatrix[16];


void InitializeVertexBuffer()
{
	glGenBuffers(1, &positionBufferObject);
	glBindBuffer(GL_ARRAY_BUFFER, positionBufferObject);
	glBufferData(GL_ARRAY_BUFFER, g_point_count * 3 * sizeof (float), &g_vp[0], GL_STATIC_DRAW);
	glGenBuffers(1, &normBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, normBuffer);
	glBufferData(GL_ARRAY_BUFFER, g_point_count * 3 * sizeof (float), &g_vn[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

//Called after the window and OpenGL are initialized. Called exactly once, before the main loop.
void init()
{
	InitializeProgram();
	loadTexture();
	InitializeVertexBuffer();

	glm::mat4 matrix = glm::scale(IdentityMat4(), glm::vec3(200.0/640.0, 200.0/480.0, 1.0));
	
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glm::mat4x4 persMatrix = glm::perspective(60.0f, 640.0f/ 480.0f, 0.5f, 100.0f);
	glm::mat4 vMatrix = g_cam.getViewMatrix();
	
	mProgram->use();
		mProgram->bindAttribLocation(0, "position");
		mProgram->bindAttribLocation(1, "norm");
		mProgram->setUniform("viewMatrix", vMatrix);
		mProgram->setUniform("transMatrix", matrixTransform);
		mProgram->setUniform("perspectiveMatrix", persMatrix);
	glUseProgram(0);

	mProgram->printActiveAttribs();
	mProgram->printActiveUniforms();

	glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);
	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);
	glDepthFunc(GL_LEQUAL);
	glDepthRange(0.0f, 1.0f);
}

//Called to update the display.
//You should call glutSwapBuffers after all of your rendering to display what you rendered.
//If you need continuous updates of the screen, call glutPostRedisplay() at the end of the function.
void display()
{
	glBindVertexArray(vao);

		mProgram->use();
			glEnableVertexAttribArray(0);
			glEnableVertexAttribArray(1);
			mProgram->setUniform("viewMatrix", g_cam.getViewMatrix());
			glBindBuffer(GL_ARRAY_BUFFER, positionBufferObject);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
			glBindBuffer(GL_ARRAY_BUFFER, normBuffer);
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
			glDrawArrays(GL_TRIANGLES, 0, g_vp.size());
		glUseProgram(0);

}

//Called whenever the window is resized. The new window size is given, in pixels.
//This is an opportunity to call glViewport or glScissor to keep up with the change in size.
void reshape (int w, int h)
{
	float fFrustumScale = 1.0f;
	theMatrix[0] = fFrustumScale / (w / (float)h);
    theMatrix[5] = fFrustumScale;
    
    glUseProgram(theProgram);
    glUniformMatrix4fv(perspectiveMatrixUnif, 1, GL_FALSE, theMatrix);
    glUseProgram(0);
    
    glViewport(0, 0, (GLsizei) w, (GLsizei) h);
}


unsigned int defaults(unsigned int displayMode, int &width, int &height) {return displayMode;}
#endif