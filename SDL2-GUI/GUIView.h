/**
 * \class GUIView
 *
 * \ingroup SDL2-GUI
 *
 * \brief Handles all rendering in SDL2-GUI
 *
 * This class holds shaders and rendering data so that
 * elements can make draw calls and only reference a 
 * single object.
 * 
 *
 * \note Should be used for all rendering.
 *
 * \author  Lee Jacobs 
 *
 * \version  1.0 
 *
 * \date  2014/06/10 
 *
 * Contact: leemichaeljacobs@gmail.com
 *
 * Created on: 2014/05/28
 *
 * $Id: doxygen-howto.html,v 1.5 2005/04/14 14:16:20 bv Exp $
 *
 */

#ifndef GUIVIEW
#define GUIVIEW

#include "GLSLShader.h"
#include<glm\glm.hpp>
#include <stdio.h>
#include <fstream>
#include<map>
#include<string>
#include <memory>
#include"GUIFont.h"

namespace SDLGUI {

//quad surface to render texture over
struct ElementSurface {

	float verts[12];

	float texture_coords[12];

	ElementSurface() {
		verts[0] = -1.0;
		verts[1] = 1.0;
		verts[2] = -1.0;
		verts[3] = -1.0;
		verts[4] = 1.0;
		verts[5] = -1.0;
		verts[6] = 1.0;
		verts[7] = -1.0;
		verts[8] = 1.0;
		verts[9] = 1.0;
		verts[10] = -1.0;
		verts[11] = 1.0;

		texture_coords[0] = 0.0;
		texture_coords[1] = 1.0;
		texture_coords[2] = 0.0;
		texture_coords[3] = 0.0;
		texture_coords[4] = 1.0;
		texture_coords[5] = 0.0;
		texture_coords[6] = 1.0;
		texture_coords[7] = 0.0;
		texture_coords[8] = 1.0;
		texture_coords[9] = 1.0;
		texture_coords[10] = 0.0;
		texture_coords[11] = 1.0;
	};

};

class GUIView {

private:
	GLuint m_vao; 
	GLuint m_vbo; 
	GLuint m_vbot; 
	std::shared_ptr<GLSLProgram> m_program;
	ElementSurface m_surface; //Surface we are rendering to
	GLuint m_errorTexture; //red texture for error checking
	std::shared_ptr<GUIFont> m_font;

public:

	GUIView( std::shared_ptr<GLSLProgram> program );
	virtual ~GUIView();

	/*!
	 * \brief renders a texture at the given position with the given scale
	 *
	 * \param texture A GLuint that is handle to a texture in GPU memory
	 * \param position A GLM::Vec2 representing the upper left hand position of the panel
	 * \param scale A GLM::Vec2 representing the width and height scale of the panel
	 *
	 * \return void
	 */
	void renderPanel( GLuint texture, glm::vec2 position, glm::vec2 scale );

	/*!
	 * \brief renders a texture at the given postion with the given scale and provides 
	 *		  the subroutine handle to be used by the panel shader.
	 *
	 * \param texture A GLuint that is handle to a texture in GPU memory
	 * \param position A GLM::Vec2 representing the upper left hand position of the panel
	 * \param scale A GLM::Vec2 representing the width and height scale of the panel
	 * \param subroutine A handle to the subroutine for the panels shader
	 *
	 * \return void
	 */
	void renderPanel( GLuint texture, glm::vec2 position, glm::vec2 scale, int subroutine );

	/*!
	 * \brief renders the given Vertex array object using the text rendering shader
	 *
	 * \param textVAO A vertex array object that is a handle to text information on the GPU
	 * \param pos_x The x position to render at
	 * \param pos_y the y position to render at
	 * \param size The size that our text should be when rendering
	 * \param numChars The number of characters that our text string has
	 *
	 * \return void
	 */
	void renderText( GLuint textVAO, float pos_x, float pos_y, int size, int numChars );

	/*!
	 * \brief render a panel at the scale of the original panel, error rendering can be turned on through the GUIManager
	 *
	 * \param position A GLM::Vec2 that represents the position to render the error at
	 * \param scale A GLM::Vec2 that represents the width and height to render the error with
	 *
	 * \return void
	 */
	void renderError( glm::vec2 position, glm::vec2 scale );

	/*!
	 * \brief sets up the view to render a panel using the panel shader and geometry
	 *
	 * \return void
	 */
	void prepareRenderer();

	/*!
	 * \brief returns the Opengl state to using the default shader
	 *
	 * \return void
	 */
	void cleanRenderer();

	/*!
	 * \brief Store text on the GPU to be rendered later
	 *
	 * \param text The string of text to be stored
	 * \param vertVBO The VBO to hold the text vertex data
	 * \param texcoordVBO The VBO to hold the text texturecoord data
	 * \param textVAO The VAO to hold the handle to the vertex data on the GPU
	 *
	 * \return void
	 */
	void cacheText( std::string text , GLuint vertVBO, GLuint texcoordVBO, GLuint textVAO ){
		m_font->cacheText(text, vertVBO, texcoordVBO, textVAO);
	}

	/*!
	 * \brief Store text on the GPU to be rendered in a multiLine format
	 *
	 * \param text The string of text to be stored
	 * \param vertVBO The VBO to hold the text vertex data
	 * \param texcoordVBO The VBO to hold the text texturecoord data
	 * \param textVAO The VAO to hold the handle to the vertex data on the GPU
	 * \param width The width of the box to render the text in
	 *
	 * \return
	 */
	void cacheTextWrap( std::string text , GLuint vertVBO, GLuint texcoordVBO, GLuint textVAO , int width ) {
		m_font->cacheTextWrap( text, vertVBO, texcoordVBO, textVAO, width );
	}

	/*!
	 * \brief update current text with more text or remove text at the updateLocation onward
	 *
	 * \param text The string of text to be stored
	 * \param vertVBO The VBO to hold the text vertex data
	 * \param texcoordVBO The VBO to hold the text texturecoord data
	 * \param textVAO The VAO to hold the handle to the vertex data on the GPU
	 * \param updateLocation The text location to update the current text at
	 *
	 * \return void
	 */
	void updateCachedText( std::string text, GLuint vertVBO, GLuint texcoordVBO, GLuint textVAO, int updateLocation ){
		m_font->updateCacheText(text, vertVBO, texcoordVBO, textVAO, updateLocation, 0 );
	}

	/*!
	 * \brief assign a texture to errors
	 *
	 * \param texture The texture handle for error textures
	 *
	 * \return void
	 */
	void assignErrorTexture( GLuint texture ){
		m_errorTexture = texture;
	}

	/*!
	 * \brief assign a font to the view
	 *
	 * \param font A GUIFont pointer that references an object
	 *
	 * \return void
	 */
	void assignFont( std::shared_ptr<GUIFont> font ){
		m_font = font;
	}


};

}

#endif