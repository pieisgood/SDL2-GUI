#ifndef GLSL_MATERIAL
#define GLSL_MATERIAL

#include"GLSLShader.h"
#include"UniformVar.h"
#include"Texture.h"
#include"VertexAttrib.h"
#include<vector>
#include<memory>

class GLSLMaterial {

private:

	std::vector< std::shared_ptr< Uniform > > m_uniforms; //uniform list
	std::vector< std::shared_ptr< Texture > > m_textures; //texture list
	std::vector< std::shared_ptr< VertexAttrib > > m_vertAttribs; //Attribute list
	std::shared_ptr< GLSLProgram > m_program; //program


	//attribute and uniform lists go here, need to look up how to work with both!
	//should also consider the task of rendering a material on top of a mesh/model!
	//A mesh/model should hold reference to the vertex attributes
	//a shader should hold reference to the uniforms and changing data!


public:
	GLSLMaterial( void );
	~GLSLMaterial( void );

	void use( void );

	void addUniform( std::shared_ptr< Uniform > uniform );
	void addTexture( std::shared_ptr< Texture > texture );
	void addVertexAttribute( std::shared_ptr< VertexAttrib > vertAttrib );
	void setProgram( std::shared_ptr< GLSLProgram > program );

	GLSLProgram* getProgram( void );

};

#endif