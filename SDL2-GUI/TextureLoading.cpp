#include"TextureLoading.h"
//#define STB_IMAGE_IMPLEMENTATION
#include"stb_image.h"
#include<assert.h>
#include<GL\glew.h>


void loadCubeMap(const char* front,
								const char* back,
								const char* top,
								const char* bottom,
								const char* left,
								const char* right,
								GLuint* tex_cube ) {
  // generate a cube-map texture to hold all the sides
  glActiveTexture (GL_TEXTURE0);
  glGenTextures (1, tex_cube);
  
  // load each image and copy into a side of the cube-map texture
  assert (
    loadCubeMapSides (*tex_cube, GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, front));
  assert (
    loadCubeMapSides (*tex_cube, GL_TEXTURE_CUBE_MAP_POSITIVE_Z, back));
  assert (
    loadCubeMapSides (*tex_cube, GL_TEXTURE_CUBE_MAP_POSITIVE_Y, top));
  assert (
    loadCubeMapSides (*tex_cube, GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, bottom));
  assert (
    loadCubeMapSides (*tex_cube, GL_TEXTURE_CUBE_MAP_NEGATIVE_X, left));
  assert (
    loadCubeMapSides (*tex_cube, GL_TEXTURE_CUBE_MAP_POSITIVE_X, right));
  // format cube map texture
  glTexParameteri (GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri (GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri (GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
  glTexParameteri (GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri (GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
}

bool loadCubeMapSides( GLuint texture, GLenum side_target, const char* file_name ) {

	glBindTexture (GL_TEXTURE_CUBE_MAP, texture);

	int x, y, n;
	int force_channels = 4;
	unsigned char*  image_data = stbi_load (
	file_name, &y , &x,  &n, force_channels);

	if (!image_data) {
		fprintf (stderr, "ERROR: could not load %s\n", file_name);
		return false;
	}

	// non-power-of-2 dimensions check
	if ((x & (x - 1)) != 0 || (y & (y - 1)) != 0) {
		fprintf (
			stderr, "WARNING: image %s is not power-of-2 dimensions\n", file_name
		);
	}
  
	// copy image data into 'target' side of cube map
	glTexImage2D (
		side_target,
		0,
		GL_RGBA,
		x,
		y,
		0,
		GL_RGBA,
		GL_UNSIGNED_BYTE,
		image_data
	);

	free (image_data);

	return true;
}

GLuint loadTexture( const char* file_name ) {
	int x, y;
	unsigned char* image = loadImage(file_name, &x, &y);

	GLuint localTexture;

	glGenTextures (1, &localTexture);
	//glActiveTexture (GL_TEXTURE0);
	glBindTexture (GL_TEXTURE_2D, localTexture);
	glTexImage2D (
	  GL_TEXTURE_2D,
	  0,
	  GL_RGBA,
	  x,
	  y,
	  0,
	  GL_RGBA,
	  GL_UNSIGNED_BYTE,
	  image
	);

	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	delete[](image);

	return localTexture;
}

unsigned char* loadImage( const char* file_name , int* x, int* y ) {
	int n;
	int force_channels = 4;
	unsigned char* image_data = stbi_load (file_name, x, y, &n, force_channels);

	if (!image_data) {
	 fprintf (stderr, "ERROR: could not load %s\n", file_name);
	}

	// NPOT check
	if ((*x & (*x - 1)) != 0 || (*y & (*y - 1)) != 0) {
	  fprintf (
		stderr, "WARNING: texture %s is not power-of-2 dimensions\n", file_name
	  );
	}

	int width_in_bytes = *x * 4;
	unsigned char *top = NULL;
	unsigned char *bottom = NULL;
	unsigned char temp = 0;
	int half_height = (*y) / 2;

	for (int row = 0; row < half_height; row++) {
	  top = image_data + row * width_in_bytes;
	  bottom = image_data + (*y - row - 1) * width_in_bytes;
	  for (int col = 0; col < width_in_bytes; col++) {
		temp = *top;
		*top = *bottom;
		*bottom = temp;
		top++;
		bottom++;
	  }
	}

	return image_data;
}
