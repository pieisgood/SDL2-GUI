#ifndef UI_STENCIL
#define UI_STENCIL


class GL_Stencil {
private:

public:
	GL_Stencil();
	~GL_Stencil();

	void bindStencil();
	void stencilRect();
	void stencilCircle();
	void stencilShape( GLuint vBuffer );

};

#endif