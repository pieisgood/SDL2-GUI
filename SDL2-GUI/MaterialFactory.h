#ifndef MATERIAL_FACTORY
#define MATERIAL_FACTORY

#include"UniformVar.h"
#include"GLSLMaterial.h"
#include"GLSLShader.h"
#include"VertexAttrib.h"
#include"Texture.h"
#include"tinyxml2.h"
#include"Mesh.h"
//#include <assimp/cimport.h> // C importer
//#include <assimp/scene.h> // collects data
//#include <assimp/postprocess.h> // various extra operations
#include <vector>
#include"TextureLoading.h"
#include"VertAttribLoading.h"
#include"CubeMap.h"

class MaterialFactory {
private:
	GLenum m_textureLocation;
	tinyxml2::XMLDocument* m_doc;
	std::shared_ptr< GLSLMaterial > m_material;

	std::shared_ptr< VertexAttrib > createVertexAttribute( tinyxml2::XMLElement* node , const aiScene* scene );
	std::shared_ptr< Uniform > createUniform( tinyxml2::XMLElement* node );
	std::shared_ptr< Texture > createTexture( tinyxml2::XMLElement* node );
	std::shared_ptr< GLSLProgram > createProgram( tinyxml2::XMLElement* node , std::shared_ptr< GLSLMaterial > material  );
	std::shared_ptr< Texture > createCubeMap( tinyxml2::XMLElement* node );

public:

	MaterialFactory( void );
	~MaterialFactory( void );

	std::shared_ptr< Mesh > createMesh( const char* meshXml );
	std::shared_ptr< GLSLMaterial > createMaterial( tinyxml2::XMLElement* node, const aiScene* scene  );
};

#endif