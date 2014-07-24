#ifndef OPENGL_CAMERA
#define OPENGL_CAMERA
#include <GL\glew.h>
#include <glm\glm.hpp>
#include <glm\gtx\rotate_vector.hpp>
#include <glm\gtx\transform.hpp>

class GL_Camera {
private:
	glm::vec3 m_pos; //Camera position in R^3
	glm::vec3 m_dir; //Direction the camera is looking
	glm::vec3 m_up;  //Cameras up direction
	glm::vec3 m_right; //Cameras right direction
	float m_pitch; //Current pitch in radians
	float m_yaw; //Current yaw in radians
	float m_speed; //Speed in the xz plane
	float m_yaw_speed; //Rotation speed
	glm::mat4 m_view;  //View Matrix

public:

	GL_Camera(): m_pos(glm::vec3(0.0,0.0,2.0)), m_dir(glm::vec3(0.0,0.0,1.0)),
		m_up(glm::vec3(0.0,1.0,0.0)), m_yaw(0) {
		m_right = glm::cross(m_dir, m_up);		
	}

	GL_Camera(glm::vec3 pos, glm::vec3 dir, glm::vec3 up, float speed, float yaw);

	~GL_Camera();

	glm::mat4 lookAt(glm::vec3 target_pos);
	void updatePosition(glm::vec3 delta);
	void withDir(float delta);
	glm::mat4 getViewMatrix();
	void mouseRotation(float deltaX, float deltaY);
	void forwardMotion(float deltaTime);
	void backwardMotion(float deltaTime);
	void rightMotion(float deltaTime);
	void leftMotion(float deltaTime);

};

GL_Camera::~GL_Camera(){

}

GL_Camera::GL_Camera(glm::vec3 pos, glm::vec3 dir, glm::vec3 up, float speed, float yaw){
	m_pos = pos;
	m_dir = dir;
	m_up = up;
	m_speed = speed;
	m_yaw_speed = yaw;
	m_yaw = 0;
}

void GL_Camera::mouseRotation(float deltaX, float deltaY){
	m_yaw += deltaX/2000.0;
	m_pitch += deltaY/2000.0;
	m_dir = glm::vec3(cos(m_pitch)*sin(m_yaw), sin(m_pitch), cos(m_pitch)*cos(m_yaw));
	m_right = glm::vec3(sin(m_yaw - 3.14f/2.0f), 0, cos(m_yaw - 3.14f/2.0f));
	m_up = glm::cross(m_right, m_dir);
}

void GL_Camera::forwardMotion(float deltaTime){
	m_pos = m_pos + deltaTime*m_dir;
}

void GL_Camera::backwardMotion(float deltaTime){
	m_pos = m_pos - deltaTime*m_dir;
}

void GL_Camera::rightMotion(float deltaTime){
	m_pos = m_pos + deltaTime*m_right;
}

void GL_Camera::leftMotion(float deltaTime){
	m_pos = m_pos - deltaTime*m_right;
}
	
glm::mat4 GL_Camera::lookAt(glm::vec3 target_pos){
	glm::mat4 temp(0.0);
	return temp;
}

void GL_Camera::updatePosition(glm::vec3 delta){
	m_pos = m_pos + delta;
}

void GL_Camera::withDir(float delta){
	m_pos = m_pos + delta*m_dir;
}

glm::mat4 GL_Camera::getViewMatrix(){
	glm::mat4 cam_view = glm::lookAt(m_pos, m_pos+m_dir, m_up);
	return cam_view;
}



#endif
