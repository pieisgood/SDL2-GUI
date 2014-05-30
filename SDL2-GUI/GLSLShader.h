#ifndef GLSLSHADER
#define GLSLSHADER
#include<string>
#include<fstream>
#include<glm\glm.hpp>
#include <gl\glew.h>

namespace GLSLShader {
	enum GLSLShaderType{
		VERTEX, FRAGMENT, GEOMETRY, TESS_CONTROL,
		TESS_EVALUATION
	};
};

class GLSLProgram {

private:

	int m_handle;
	bool m_linked;
	std::string m_logString;

	int getUniformLocation( const char* name ); 
	bool fileExists( const std::string & fileName ); 

public:

	GLSLProgram();
	virtual ~GLSLProgram();

	bool compileShaderFromFile( const char* fileName, GLSLShader::GLSLShaderType type );
	bool compileShaderFromString( const std::string & source, GLSLShader::GLSLShaderType type ); 
	bool link(); 
	void use(); 
	std::string log();
	int getHandle(); 
	bool isLinked();
	void bindAttribLocation( GLuint location, const char* name );
	void bindFragDataLocation( GLuint location,  const char* name );
	void setUniform( const char *name, const glm::vec3 & v );
	void setUniform( const char *name, const glm::vec4 & v );
	void setUniform( const char *name, const glm::mat4 & m );
	void setUniform( const char *name, const glm::mat3 & m );
	void setUniform( const char *name, const glm::vec2 & v );
	void setUniform( const char *name, float val );
	void setUniform( const char *name, int val );
	void setUniform( const char *name, bool val );
	void setUniform( const char *name, float x, float y );
	void setUniform( const char *name, float x, float y, float z );
	void setUniform( const char *name, float x, float y, float z, float w );

	void printActiveUniforms();
	void printActiveAttribs();
};



#endif