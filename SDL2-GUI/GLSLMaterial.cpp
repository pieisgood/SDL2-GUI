#include"GLSLMaterial.h"

GLSLMaterial::GLSLMaterial( void ) { }
GLSLMaterial::~GLSLMaterial( void ) { }


void GLSLMaterial::addUniform( std::shared_ptr< Uniform > uniform ) {
	m_uniforms.push_back( uniform );
}

void GLSLMaterial::addTexture( std::shared_ptr< Texture > texture ) {
	m_textures.push_back( texture );
}

void GLSLMaterial::addVertexAttribute( std::shared_ptr< VertexAttrib > vertAttrib ) {
	m_vertAttribs.push_back( vertAttrib );
}

void GLSLMaterial::setProgram( std::shared_ptr< GLSLProgram > program ) {
	m_program = program;
}

void GLSLMaterial::use( void ) {

	m_program->use();

	GLenum glErr;

    glErr = glGetError();
    if (glErr != GL_NO_ERROR)
    {
        printf("glError %i\n", glErr);
    }

	auto uniformIt = m_uniforms.begin();
	for( ; uniformIt != m_uniforms.end(); uniformIt++ ) {
		(*uniformIt)->loadUniform( m_program->getHandle() );
		 glErr = glGetError();
		if (glErr != GL_NO_ERROR)
		{
			printf("glError %i\n", glErr);
		}
	}

	auto vertAttribIt = m_vertAttribs.begin();
	for( ; vertAttribIt != m_vertAttribs.end() ; vertAttribIt++ ) {
		(*vertAttribIt)->bindAttrib();
		 glErr = glGetError();
		if (glErr != GL_NO_ERROR)
		{
			printf("glError %i\n", glErr);
		}
	}

	auto textureIt = m_textures.begin();
	for( ; textureIt != m_textures.end() ; textureIt++ ) {
		(*textureIt)->bindTexture();
		glErr = glGetError();
		if (glErr != GL_NO_ERROR)
		{
			printf("glError %i\n", glErr);
		}
	}

}

GLSLProgram* GLSLMaterial::getProgram( void ) {
	return m_program.get();
}