#ifndef TEXTURE_LOADING
#define TEXTURE_LOADING

#include<GL\glew.h>


void loadCubeMap(const char* front,
								const char* back,
								const char* top,
								const char* bottom,
								const char* left,
								const char* right,
								GLuint* tex_cube );

bool loadCubeMapSides( GLuint texture, GLenum side_target, const char* file_name );
GLuint loadTexture( const char* file_name );
unsigned char* loadImage( const char* file_name , int* x, int* y );

#endif