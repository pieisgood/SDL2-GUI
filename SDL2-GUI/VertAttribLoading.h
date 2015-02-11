#ifndef VERTEX_ATTRIBUTE_LOADING
#define VERTEX_ATTRIBUTE_LOADING

#include <assimp/cimport.h> // C importer
#include <assimp/scene.h> // collects data
#include <assimp/postprocess.h> // various extra operations
#include <GL\glew.h>

void LoadVertexNormalAttribute( const aiScene* scene , GLuint* vBuffer );
void LoadVertexColorAttribute( const aiScene* scene ,  GLuint* vBuffer );
void LoadVertexTexCoordAttribute( const aiScene* scene ,  GLuint* vBuffer );
void LoadVertexTangentAttribute( const aiScene* scene , GLuint* vBuffer );
void LoadVertexBiTangentAttribute( const aiScene* scene ,  GLuint* vBuffer );
void LoadVertexPositionAttribute( const aiScene* scene ,  GLuint* vBuffer );


#endif