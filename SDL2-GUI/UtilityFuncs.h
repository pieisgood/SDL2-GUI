#include <assimp/cimport.h> // C importer
#include <assimp/scene.h> // collects data
#include <assimp/postprocess.h> // various extra operations
#include <vector> 
#include <stdio.h> 

#include <glm\glm.hpp>

std::vector<float> g_vp, g_vt, g_vn;
int g_point_count = 0;
GLuint tex;

glm::mat4 PerspectiveMatrix( float fov, float aspect, float zFar, float zNear ) {
	glm::mat4 pMatrix(0.0);
	float range = tan(fov * 0.5) * zNear;

	pMatrix[0][0] = (2.0*zNear)/(range * aspect + range * aspect);
	pMatrix[1][1] = zNear / range;
	pMatrix[2][2] = (zFar + zNear) / (zNear - zFar);
	pMatrix[2][3] = (2 * zFar * zNear) / (zNear - zFar);
	pMatrix[3][2] = -1.0f;

	return pMatrix;
}

glm::mat4 IdentityMat4(){
	glm::mat4 identity;

	identity[0][0] = 1.0;
	identity[1][1] = 1.0;
	identity[2][2] = 1.0;
	identity[3][3] = 1.0;

	return identity;
}

glm::mat4 Translate( glm::mat4 mat, glm::vec3 trans ) {
	mat[0][4] = trans[0];
	mat[1][4] = trans[1];
	mat[2][4] = trans[2];
	return mat;
}


bool loadTexture(){
	SDL_Surface* textureImage = SDL_LoadBMP("testTexture.bmp");

	glGenTextures (1, &tex);
	glActiveTexture (GL_TEXTURE0);
	glBindTexture (GL_TEXTURE_2D, tex);
	glTexImage2D (
	  GL_TEXTURE_2D,
	  0,
	  GL_RGB,
	  textureImage->w,
	  textureImage->h,
	  0,
	  GL_BGR,
	  GL_UNSIGNED_BYTE,
	  textureImage->pixels
	);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	return true;
}

bool loadMesh( const char* file_name ) {
	const aiScene* scene = aiImportFile (file_name, aiProcess_Triangulate); // TRIANGLES!

	if (!scene) {
		fprintf (stderr, "ERROR: reading mesh %s\n", file_name);
		return false;
	}

	printf ("  %i animations\n", scene->mNumAnimations);
	printf ("  %i cameras\n", scene->mNumCameras);
	printf ("  %i lights\n", scene->mNumLights);
	printf ("  %i materials\n", scene->mNumMaterials);
	printf ("  %i meshes\n", scene->mNumMeshes);
	printf ("  %i textures\n", scene->mNumTextures);

	for (unsigned int m_i = 0; m_i < scene->mNumMeshes; m_i++) {

		const aiMesh* mesh = scene->mMeshes[m_i];
		printf ("    %i vertices in mesh\n", mesh->mNumVertices);
		g_point_count = mesh->mNumVertices;

		for (unsigned int v_i = 0; v_i < mesh->mNumVertices; v_i++) {
		  if (mesh->HasPositions ()) {
			const aiVector3D* vp = &(mesh->mVertices[v_i]);
			//printf ("      vp %i (%f,%f,%f)\n", v_i, vp->x, vp->y, vp->z);
			g_vp.push_back (vp->x);
			g_vp.push_back (vp->y);
			g_vp.push_back (vp->z);
		  }
		  if (mesh->HasNormals ()) {
			const aiVector3D* vn = &(mesh->mNormals[v_i]);
			//printf ("      vn %i (%f,%f,%f)\n", v_i, vn->x, vn->y, vn->z);
			g_vn.push_back (vn->x);
			g_vn.push_back (vn->y);
			g_vn.push_back (vn->z);
		  }
		  if (mesh->HasTextureCoords (0)) {
			const aiVector3D* vt = &(mesh->mTextureCoords[0][v_i]);
			//printf ("      vt %i (%f,%f)\n", v_i, vt->x, vt->y);
			g_vt.push_back (vt->x);
			g_vt.push_back (vt->y);
		  }
		  if (mesh->HasTangentsAndBitangents ()) {
			// NB: could store/print tangents here
			}
		}
	}

	printf(" %i normals in mesh\n", g_vn.size()/3);

	aiReleaseImport(scene);
	return true;
}

void meshToBuffer() {
	unsigned int vbo = 0;
	unsigned int nbo = 0;
	glGenBuffers(1, &vbo);
	glBindBuffer (GL_ARRAY_BUFFER, vbo);
	glBufferData (GL_ARRAY_BUFFER, g_point_count * 3 * sizeof (float), &g_vp[0],
		GL_STATIC_DRAW);
	unsigned int vao = 0;
	glGenVertexArrays (1, &vao);
	glBindVertexArray (vao);
	glEnableVertexAttribArray (0);
	glBindBuffer (GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer (0, 3, GL_FLOAT, GL_FALSE, 0, (GLubyte*)NULL);
}