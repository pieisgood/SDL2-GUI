/**
 * \class GUIFont
 *
 * \ingroup SDL2-GUI
 *
 * \brief Font Rendering and Management class
 *
 * This class is meant to help generate and render text.
 * Outside tools can be used to generate the distance field
 * and char descriptor files. These are provided under the
 * tools folder in SDL2-GUI.
 *
 * \note Text rendering made easy.
 *
 * \author  Lee Jacobs 
 *
 * \version  1.0 
 *
 * \date 2014/06/10 
 *
 * Contact: leemichaeljacobs@gmail.com
 *
 * Created on: 2014/05/28
 *
 * $Id: doxygen-howto.html,v 1.5 2005/04/14 14:16:20 bv Exp $
 *
 */

#ifndef GUIFONT
#define GUIFONT
#include<string>
#include"GLSLShader.h"
#include<vector>
#include <memory>

namespace SDLGUI {

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
	std::shared_ptr<GLSLProgram> m_fontProgram;
	GLuint m_fontTexture;
	GLuint m_textVAO; //our vertex attributes for fonts/text
	const char* m_fontData;
	glm::vec3 m_color;
	float m_alpha;


	bool parseFont( std::istream& Stream );
	GUIFont(){};

public:

	GUIFont( GLuint fontTexture , const char* fontData , std::shared_ptr<GLSLProgram> fontProgram );
	~GUIFont();


	void renderText( std::string text , float x , float y , int size ); //render text to screen

	/*!
	 * \brief Used to render cached text in the form of a Vertex Array Object
	 *
	 * \param textVAO a GLuint that represents the vertex array object referencing the buffer objects on the gpu
	 * \param x the x position to render the text at
	 * \param y the y position to render the text at
	 * \param size the size to render the text at
	 * \param stringSize the length of the string, needed to properly call the glDrawArrays function
	 *
	 * \return void
	 */
	void renderText( GLuint textVAO , float x, float y, int size, int stringSize);

	/*!
	 * \brief Used to update the color of the text to be rendered
	 *
	 * \param color A GLM Vec3 representing the color of the text
	 *
	 * \return void
	 */
	void assignColor( glm::vec3 color );

	/*!
	 * \brief Used to update the transparency of the text to be rendered
	 *
	 * \param alpha A float value from 0.0f to 1.0f representing the transparency of the text
	 *
	 * \return void
	 */
	void assignTransparency( float alpha );

	/*!
	 * \brief Used to cache text for future rendering
	 *
	 * \param text A string that represents the text to be used in the cache
	 * \param vertVBO The vertex buffer object that will store our text verticies
	 * \param texcoordVBO The vertex buffer object that will store our texture coordinates for our text verticies
	 * \param textVAO The vertex array object we will call when rendering our text to the screen
	 *
	 * \return
	 */
	GLuint cacheText( std::string text, GLuint vertVBO, GLuint texcoordVBO, GLuint textVAO  );

	/*!
	 * \brief Used to cache text in a bounded box and allows for simple word wrapping. 
	 *
	 * \param text A string that represents the text to be used in the cache
	 * \param vertVBO The vertex buffer object that will store our text verticies
	 * \param texcoordVBO The vertex buffer object that will store our texture coordinates for our text verticies
	 * \param textVAO The vertex array object we will call when rendering our text to the screen
	 * \param width The width of the text box in pixels
	 *
	 * \return
	 */
	GLuint cacheTextWrap( std::string text, GLuint vertVBO, GLuint texcoordVBO, GLuint textVAO , int width ); 

	/*!
	 * \brief Used to update a small portion of cached text, for dynamic updating of text
	 *
	 * \param text A string that represents the text to be used in the cache
	 * \param vertVBO The vertex buffer object that will store our text verticies
	 * \param texcoordVBO The vertex buffer object that will store our texture coordinates for our text verticies
	 * \param textVAO The vertex array object we will call when rendering our text to the screen
	 * \param updateLocation the character location to start updating from
	 * \param CurY the Y location in pixels to draw the new text
	 * \param CurX the X location in pixels to draw the new text
	 *
	 * \return
	 */
	GLuint updateCacheText( std::string text,GLuint vertVBO, GLuint texcoordVBO, GLuint textVAO , int updateLocation, int CurY = 0, int CurX = 0 );

	/*!
	 * \brief Used to fill the Verts vector and Texcoords vector with the proper geometry information to store in a buffer object
	 *
	 * \param text A string that represents the text data to be stored in the vectors
	 * \param Verts A reference to a vector of floats to be filled with 2D vertex data
	 * \param Texcoords A reference to a vector of floats to be filled with texture coordinate data
	 * \param CurY the Y location in pixels to draw the new text
	 * \param CurX the X location in pixels to draw the new text
	 *
	 * \return void
	 */
	void textListFill( std::string text, std::vector<float> &Verts, std::vector<float> &Texcoords , int CurY = 0 , int CurX = 0 );

};

}

#endif