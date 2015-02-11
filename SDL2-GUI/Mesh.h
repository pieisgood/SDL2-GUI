#ifndef GLSL_MESH
#define GLSL_MESH

#include<GL\glew.h>
#include"GLSLMaterial.h"

class Mesh {
private:
	int m_size;
	GLuint m_vao;
	std::shared_ptr< GLSLMaterial > m_material;

public:
	Mesh( void );
	~Mesh( void );

	void draw( glm::mat4 model , glm::mat4 view , glm::mat4 projection );

	void setSize( int size );
	void setVAO( GLuint vao );
	void setMaterial( std::shared_ptr< GLSLMaterial > material );


};

#endif