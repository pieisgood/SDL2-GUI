#include "VertAttribLoading.h"
#include <assimp/cimport.h> // C importer
#include <assimp/postprocess.h> // various extra operations
#include<vector>

void LoadVertexNormalAttribute( const aiScene* scene , GLuint* vBuffer ) {
	std::vector<float> g_vn;

	int g_point_count = 0;

	for (unsigned int m_i = 0; m_i < scene->mNumMeshes; m_i++) {

		const aiMesh* mesh = scene->mMeshes[m_i];
		printf ("    %i vertices in mesh\n", mesh->mNumVertices);
		g_point_count = mesh->mNumVertices;

		for (unsigned int v_i = 0; v_i < mesh->mNumVertices; v_i++) {

			if ( mesh->HasNormals() ) {
				const aiVector3D* vn = &(mesh->mNormals[v_i]);
				//printf ("      vn %i (%f,%f,%f)\n", v_i, vn->x, vn->y, vn->z);
				g_vn.push_back (vn->x);
				g_vn.push_back (vn->y);
				g_vn.push_back (vn->z);
			}

		}

	}



	glGenBuffers( 1, vBuffer );
	glBindBuffer( GL_ARRAY_BUFFER, *vBuffer );
	glBufferData( GL_ARRAY_BUFFER, g_point_count * 3 * sizeof (float), &g_vn[0], GL_STATIC_DRAW );
	glVertexAttribPointer( 1, 3, GL_FLOAT, GL_FALSE, 0, 0 );

	glBindBuffer( GL_ARRAY_BUFFER, 0 );
}

void LoadVertexColorAttribute( const aiScene* scene , GLuint* vBuffer ) {
	std::vector<float> g_vn;

	int g_point_count = 0;

	for (unsigned int m_i = 0; m_i < scene->mNumMeshes; m_i++) {

		const aiMesh* mesh = scene->mMeshes[m_i];
		printf ("    %i vertices in mesh\n", mesh->mNumVertices);
		g_point_count = mesh->mNumVertices;

		for (unsigned int v_i = 0; v_i < mesh->mNumVertices; v_i++) {

			if ( mesh->HasNormals() ) {
				const aiVector3D* vn = &(mesh->mNormals[v_i]);
				//printf ("      vn %i (%f,%f,%f)\n", v_i, vn->x, vn->y, vn->z);
				g_vn.push_back (vn->x);
				g_vn.push_back (vn->y);
				g_vn.push_back (vn->z);
			}

		}

	}



	glGenBuffers( 1, vBuffer );
	glBindBuffer( GL_ARRAY_BUFFER, *vBuffer );
	glBufferData( GL_ARRAY_BUFFER, g_point_count * 3 * sizeof (float), &g_vn[0], GL_STATIC_DRAW );
	glVertexAttribPointer( 5, 3, GL_FLOAT, GL_FALSE, 0, 0 );

	glBindBuffer( GL_ARRAY_BUFFER, 0 );
}

void LoadVertexTangentAttribute( const aiScene* scene , GLuint* vBuffer  ) {
	std::vector<float> g_vn;

	int g_point_count = 0;

	for (unsigned int m_i = 0; m_i < scene->mNumMeshes; m_i++) {

		const aiMesh* mesh = scene->mMeshes[m_i];
		printf ("    %i vertices in mesh\n", mesh->mNumVertices);
		g_point_count = mesh->mNumVertices;

		for (unsigned int v_i = 0; v_i < mesh->mNumVertices; v_i++) {

			if ( mesh->HasTangentsAndBitangents() ) {
				const aiVector3D* vn = &(mesh->mTangents[0]);
				//printf ("      vn %i (%f,%f,%f)\n", v_i, vn->x, vn->y, vn->z);
				g_vn.push_back (vn->x);
				g_vn.push_back (vn->y);
				g_vn.push_back (vn->z);
			}

		}

	}



	glGenBuffers( 1, vBuffer );
	glBindBuffer( GL_ARRAY_BUFFER, *vBuffer );
	glBufferData( GL_ARRAY_BUFFER, g_point_count * 3 * sizeof (float), &g_vn[0], GL_STATIC_DRAW );
	glVertexAttribPointer( 3, 3, GL_FLOAT, GL_FALSE, 0, 0 );

	glBindBuffer( GL_ARRAY_BUFFER, 0 );
}

void LoadVertexBiTangentAttribute( const aiScene* scene ,  GLuint* vBuffer ) {
	std::vector<float> g_vn;

	int g_point_count = 0;

	for (unsigned int m_i = 0; m_i < scene->mNumMeshes; m_i++) {

		const aiMesh* mesh = scene->mMeshes[m_i];
		printf ("    %i vertices in mesh\n", mesh->mNumVertices);
		g_point_count = mesh->mNumVertices;

		for (unsigned int v_i = 0; v_i < mesh->mNumVertices; v_i++) {

			if ( mesh->HasTangentsAndBitangents() ) {
				const aiVector3D* vn = &(mesh->mBitangents[0]);
				//printf ("      vn %i (%f,%f,%f)\n", v_i, vn->x, vn->y, vn->z);
				g_vn.push_back (vn->x);
				g_vn.push_back (vn->y);
				g_vn.push_back (vn->z);
			}

		}

	}


	glGenBuffers( 1, vBuffer );
	glBindBuffer( GL_ARRAY_BUFFER, *vBuffer );
	glBufferData( GL_ARRAY_BUFFER, g_point_count * 3 * sizeof (float), &g_vn[0], GL_STATIC_DRAW );
	glVertexAttribPointer( 4, 3, GL_FLOAT, GL_FALSE, 0, 0 );

	glBindBuffer( GL_ARRAY_BUFFER, 0 );
}

void LoadVertexPositionAttribute( const aiScene* scene ,  GLuint* vBuffer ) {
	
	std::vector<float> g_vp;

	int g_point_count = 0;

	for (unsigned int m_i = 0; m_i < scene->mNumMeshes; m_i++) {

		const aiMesh* mesh = scene->mMeshes[m_i];
		printf ("    %i vertices in mesh\n", mesh->mNumVertices);
		g_point_count = mesh->mNumVertices;

		for (unsigned int v_i = 0; v_i < mesh->mNumVertices; v_i++) {

			if ( mesh->HasPositions () ) {
				const aiVector3D* vp = &(mesh->mVertices[v_i]);
				//printf ("      vp %i (%f,%f,%f)\n", v_i, vp->x, vp->y, vp->z);
				g_vp.push_back (vp->x);
				g_vp.push_back (vp->y);
				g_vp.push_back (vp->z);
			}

		}

	}


	glGenBuffers( 1, vBuffer );
	glBindBuffer( GL_ARRAY_BUFFER, *vBuffer );
	glBufferData( GL_ARRAY_BUFFER, g_point_count * 3 * sizeof (float), &g_vp[0], GL_STATIC_DRAW );
	glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 0, 0 );


	glBindBuffer( GL_ARRAY_BUFFER, 0 );

}

void LoadVertexTexCoordAttribute( const aiScene* scene ,  GLuint* vBuffer ) {

	std::vector<float> g_vt;

	int g_point_count = 0;


	for (unsigned int m_i = 0; m_i < scene->mNumMeshes; m_i++) {

		const aiMesh* mesh = scene->mMeshes[m_i];
		printf ("    %i vertices in mesh\n", mesh->mNumVertices);
		g_point_count = mesh->mNumVertices;

		for (unsigned int v_i = 0; v_i < mesh->mNumVertices; v_i++) {

		  if (mesh->HasTextureCoords (0)) {
			const aiVector3D* vt = &(mesh->mTextureCoords[0][v_i]);
			//printf ("      vt %i (%f,%f)\n", v_i, vt->x, vt->y);
			g_vt.push_back (vt->x);
			g_vt.push_back (vt->y);
		  }

		}

	}


	glGenBuffers( 1, vBuffer );
	glBindBuffer( GL_ARRAY_BUFFER, *vBuffer );
	glBufferData( GL_ARRAY_BUFFER, g_point_count * 2 * sizeof (float), &g_vt[0], GL_STATIC_DRAW );
	glVertexAttribPointer( 2, 2, GL_FLOAT, GL_FALSE, 0, 0 );

	glBindBuffer( GL_ARRAY_BUFFER, 0 );
}