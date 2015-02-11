#include"MaterialFactory.h"


MaterialFactory::MaterialFactory( void ) {
	m_textureLocation = GL_TEXTURE0;
}

MaterialFactory::~MaterialFactory( void ) {}

std::shared_ptr< Mesh > MaterialFactory::createMesh( const char* meshXml ) {

	std::shared_ptr< Mesh > mesh = std::shared_ptr< Mesh >( new Mesh() );
	m_material = std::shared_ptr< GLSLMaterial >( new GLSLMaterial() );

	m_doc = new tinyxml2::XMLDocument();

	if( m_doc->LoadFile( meshXml ) ) {
		printf("loading xml file error");
		return NULL;
	}

	tinyxml2::XMLNode* child = m_doc->FirstChild();

	const char* meshFile = child->ToElement()->Attribute( "file" );

	int g_point_count = 0;
	GLuint vao;

	const aiScene* scene = aiImportFile (meshFile, aiProcess_Triangulate); // TRIANGLES!

	if (!scene) {
		fprintf (stderr, "ERROR: reading mesh %s\n", meshFile);
		return false;
	}

	glGenVertexArrays( 1, &vao );
	glBindVertexArray( vao );

	mesh->setVAO( vao );

	g_point_count = scene->mMeshes[0]->mNumVertices;

	mesh->setSize( g_point_count );
	

	for( tinyxml2::XMLElement* loopNode =child->FirstChildElement(); loopNode != NULL; loopNode=loopNode->NextSiblingElement() ) {
		
		if( strcmp( loopNode->Name() , "Material" ) == 0 ) {

			mesh->setMaterial( createMaterial( loopNode, scene ) );

		}

	}

	aiReleaseImport( scene );

	glBindVertexArray( 0 );

	m_textureLocation = GL_TEXTURE0;

	return mesh;

}

std::shared_ptr< GLSLMaterial > MaterialFactory::createMaterial( tinyxml2::XMLElement* node , const aiScene* scene ) {

	std::shared_ptr< GLSLMaterial > myMaterial = std::shared_ptr< GLSLMaterial > ( new GLSLMaterial() );

	for( tinyxml2::XMLElement* loopNode = node->FirstChildElement(); loopNode != NULL; loopNode=loopNode->NextSiblingElement() ) {
		
		if( strcmp( loopNode->Name() , "vertex_attribute" ) == 0 ) {

			myMaterial->addVertexAttribute( createVertexAttribute( loopNode , scene ) );

		}
		else if( strcmp( loopNode->Name() , "program" ) == 0 ) {

			myMaterial->setProgram( createProgram( loopNode , myMaterial ) );

		}

	}

	return myMaterial;

}

std::shared_ptr< VertexAttrib > MaterialFactory::createVertexAttribute( tinyxml2::XMLElement* node , const aiScene* scene ) {

	std::shared_ptr< VertexAttrib > vertA = std::shared_ptr< VertexAttrib >( new VertexAttrib() );

	m_material->addVertexAttribute( vertA );

	GLuint vertBuffer;

	const char* type = node->Attribute( "type" );

	if( strcmp( type , "position" ) == 0 ) {
		LoadVertexPositionAttribute( scene , &vertBuffer );
		vertA->setVBO( vertBuffer );
		vertA->setName( node->Attribute( "name" ) );
	}

	if( strcmp( type , "normal" ) == 0 ) {
		LoadVertexNormalAttribute( scene , &vertBuffer );
		vertA->setVBO( vertBuffer );
		vertA->setName( node->Attribute( "name" ) );
	}

	if( strcmp( type , "texture_coordinate" ) == 0 ) {
		LoadVertexTexCoordAttribute( scene , &vertBuffer );
		vertA->setVBO( vertBuffer );
		vertA->setName( node->Attribute( "name" ) );
	}

	if( strcmp( type , "tangent" ) == 0 ) {
		LoadVertexTangentAttribute( scene , &vertBuffer );
		vertA->setVBO( vertBuffer );
		vertA->setName( node->Attribute( "name" ) );
	}

	if( strcmp( type , "bitangent" ) == 0 ) {
		LoadVertexBiTangentAttribute( scene , &vertBuffer );
		vertA->setVBO( vertBuffer );
		vertA->setName( node->Attribute( "name" ) );
	}
		
	return vertA;
}

std::shared_ptr< Uniform > MaterialFactory::createUniform( tinyxml2::XMLElement* node ) {
	return NULL;
}

std::shared_ptr< Texture > MaterialFactory::createTexture( tinyxml2::XMLElement* node ) {

	std::shared_ptr< Texture > myTexture = std::shared_ptr< Texture > ( new Texture() );

	GLuint textureId = loadTexture( node->Attribute( "file" ) );

	myTexture->setTexture( node->Attribute( "name" ) , textureId , m_textureLocation );

	printf( " Loaded texture2D - \n ");
	printf( "	name: %s \n" , node->Attribute( "name" ) );
	printf( "	file: %s \n" , node->Attribute( "file" ) );
	printf( "	textureId: %i \n" , textureId );
	printf( "	textureLocation: %i \n", m_textureLocation );

	m_textureLocation++;

	return myTexture;

}

std::shared_ptr< Texture > MaterialFactory::createCubeMap( tinyxml2::XMLElement* node ) {

	std::shared_ptr< Texture > myTexture = std::shared_ptr< Texture > ( new CubeMap() );

	GLuint textureId;

	loadCubeMap( node->Attribute( "front" ) , node->Attribute( "back" ) , node->Attribute( "top" ) ,
		node->Attribute( "bottom" ) , node->Attribute( "left" ) , node->Attribute( "right" ) , &textureId );

	myTexture->setTexture( node->Attribute( "name" ) , textureId , m_textureLocation );

	printf( " Loaded cubeMap - \n ");
	printf( "	name: %s \n" , node->Attribute( "name" ) );
	printf( "	textureId: %i \n" , textureId );
	printf( "	textureLocation: %i \n", m_textureLocation );

	m_textureLocation++;

	return myTexture;

}

std::shared_ptr< GLSLProgram > MaterialFactory::createProgram( tinyxml2::XMLElement* node , std::shared_ptr< GLSLMaterial > material ) {

	std::shared_ptr< GLSLProgram > program = std::shared_ptr< GLSLProgram > ( new GLSLProgram() );
	const char* vertexShaderFile;
	const char* fragmentShaderFile;

	for( tinyxml2::XMLElement* loopNode = node->FirstChildElement(); loopNode != NULL; loopNode=loopNode->NextSiblingElement() ) {

		if( strcmp( loopNode->Name() , "vertex_shader" ) == 0 ) {
			vertexShaderFile = loopNode->Attribute( "source" );
		}
		else if ( strcmp( loopNode->Name() , "fragment_shader" ) == 0 ) {
			fragmentShaderFile = loopNode->Attribute( "source" );
		}
		else if ( strcmp( loopNode->Name() , "texture2D" ) == 0 ) {
			material->addTexture( createTexture( loopNode ) );
		}
		else if ( strcmp( loopNode->Name() , "cubeMap" ) == 0 ) {
			material->addTexture( this->createCubeMap( loopNode ) );
		}

	}

	program->compileShaderFromFile( vertexShaderFile , GLSLShader::VERTEX );
	program->compileShaderFromFile( fragmentShaderFile, GLSLShader::FRAGMENT );

	program->link();

	return program;

}
