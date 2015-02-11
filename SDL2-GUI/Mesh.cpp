#include"Mesh.h"

Mesh::Mesh( void ) : m_size( 0 ) , m_vao( 0 ) {}
Mesh::~Mesh( void ) {}

void Mesh::draw( glm::mat4 model , glm::mat4 view , glm::mat4 projection ) {
	static bool testAttributes = true;
	glBindVertexArray( m_vao );
	m_material->use();
		glEnableVertexAttribArray( 0 );
		glEnableVertexAttribArray( 1 );
		glEnableVertexAttribArray( 2 );
	m_material->getProgram()->setUniform( "transMatrix" , model );
	m_material->getProgram()->setUniform( "viewMatrix" , view );
	m_material->getProgram()->setUniform( "perspectiveMatrix" , projection );
	
	glDrawArrays( GL_TRIANGLES , 0 , m_size );
	
    GLenum glErr;

	if( testAttributes ) {
		testAttributes = false;
		m_material->getProgram()->printActiveAttribs();
		m_material->getProgram()->printActiveUniforms();
	}

    glErr = glGetError();
    if (glErr != GL_NO_ERROR)
    {
        printf("glError %i\n", glErr);
    }
	glUseProgram( 0 );

}

void Mesh::setSize( int size ) {
	m_size = size;
}

void Mesh::setVAO( GLuint vao ) {
	m_vao = vao;
}

void Mesh::setMaterial( std::shared_ptr< GLSLMaterial > material ) {
	m_material = material;
}