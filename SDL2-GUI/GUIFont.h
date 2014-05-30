#ifndef GUIFONT
#define GUIFONT
#include<string>
#include"GLSLShader.h"
#include<vector>


struct CharDescriptor
{
	//clean 16 bytes
	unsigned short x, y;
	unsigned short Width, Height;
	float XOffset, YOffset;
	float XAdvance;
	unsigned short Page;

	CharDescriptor() : x( 0 ), y( 0 ), Width( 0 ), Height( 0 ), XOffset( 0 ), YOffset( 0 ),
		XAdvance( 0 ), Page( 0 )
	{ }
};

struct Charset
{
	unsigned short LineHeight;
	unsigned short Base;
	unsigned short Width, Height;
	unsigned short Pages;
	CharDescriptor Chars[256];
};

class GUIFont {

private:
	Charset m_charSet;
	GLSLProgram* m_fontProgram;
	GLuint m_fontTexture;
	GLuint m_textVAO; //our vertex attributes for fonts/text
	const char* m_fontData;
	glm::vec3 m_color;
	float m_alpha;


	bool parseFont( std::istream& Stream );
	GUIFont(){};

public:

	GUIFont( GLuint fontTexture , const char* fontData , GLSLProgram* fontProgram );
	~GUIFont();


	void renderText( std::string text , float x , float y , int size ); //render text to screen
	void renderText( GLuint textVAO , float x, float y, int size, int stringSize);
	void assignColor( glm::vec3 color );
	void assignTransparency( float alpha );
	GLuint cacheText( std::string text, GLuint vertVBO, GLuint texcoordVBO, GLuint textVAO  ); 
	GLuint cacheTextWrap( std::string text, GLuint vertVBO, GLuint texcoordVBO, GLuint textVAO , int width ); 
	GLuint updateCacheText( std::string text,GLuint vertVBO, GLuint texcoordVBO, GLuint textVAO , int updateLocation, int CurY = 0 );
	void textListFill( std::string text, std::vector<float> &Verts, std::vector<float> &Texcoords , int CurY = 0 , int CurX = 0 );

};

#endif