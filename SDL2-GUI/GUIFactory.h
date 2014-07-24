/**
 * \class GUIFactory
 *
 * \ingroup SDL2-GUI
 *
 * \brief A class that builds GUIManagers from html documents
 *
 * This class, when handed an html file, will build GUIManager
 * objects as well as all Element objects that are children to 
 * the GUIManager. This allows for a simple call to build new
 * GUIManagers and to allow for ease of use.
 *
 * \note Should be used to build baseline GUIManagers
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

#ifndef SDLGUIFACTORY
#define SDLGUIFACTORY
#include <iostream>
#include <fstream>
#include "GUIManager.h"
#include "tinyxml2.h"


class GUIFactory {
private:
		tinyxml2::XMLDocument* m_doc; //our XML document
		GUIView* m_view;
		GUIManager* m_manager;
		int m_windowWidth;
		int m_windowHeight;

	/*!
	 * \brief
	 *
	 * \param
	 *
	 * \return
	 */
	Element* newElement( tinyxml2::XMLElement* type, Element* parent );

	/*!
	 * \brief
	 *
	 * \param
	 *
	 * \return
	 */
	Element* newButton(int x, int y, int width, int height, const char* id, Element* parent, const char* texture, glm::vec2 scale);

	/*!
	 * \brief
	 *
	 * \param
	 *
	 * \return
	 */
	Element* newLayout(int x, int y, int width, int height, const char* id, Element* parent, glm::vec2 scale);

	/*!
	 * \brief
	 *
	 * \param
	 *
	 * \return
	 */
	Element* newTextBox( int x, int y, int width, int height, const char* id, Element* parent, glm::vec2 scale, std::string text, GUIView* view);

	/*!
	 * \brief
	 *
	 * \param
	 *
	 * \return
	 */
	Element* handleButton(tinyxml2::XMLElement* buttonElement, Element* parent);

	/*!
	 * \brief
	 *
	 * \param
	 *
	 * \return
	 */
	Element* handleLayout(tinyxml2::XMLElement* layoutElement, Element* parent);

	/*!
	 * \brief
	 *
	 * \param
	 *
	 * \return
	 */
	GUIFont* newGUIFont(const char* fontTexture , const char* fontData , GLSLProgram* fontProgram);

	/*!
	 * \brief
	 *
	 * \param
	 *
	 * \return
	 */
	unsigned char* loadImage(const char* file, int* x, int* y);

	/*!
	 * \brief
	 *
	 * \param
	 *
	 * \return
	 */
	void iterateTree( tinyxml2::XMLElement* node, Element* parent);

	/*!
	 * \brief
	 *
	 * \param
	 *
	 * \return
	 */
	GLuint newTexture(const char* file);

	/*!
	 * \brief
	 *
	 * \param
	 *
	 * \return
	 */
	GLSLProgram* newProgram( const char* vertShader, const char* fragShader);

	/*!
	 * \brief
	 *
	 * \param
	 *
	 * \return
	 */
	glm::vec2 getPos( float x, float y );

	/*!
	 * \brief
	 *
	 * \param
	 *
	 * \return
	 */
	glm::vec4 createStencil( Element* el, Element* parent );

	/*!
	 * \brief
	 *
	 * \param
	 *
	 * \return
	 */
	void alignElementLeft( Element* el, Element* parent );

	/*!
	 * \brief
	 *
	 * \param
	 *
	 * \return
	 */
	void alignElementRight( Element* el, Element* parent );

	/*!
	 * \brief
	 *
	 * \param
	 *
	 * \return
	 */
	void alignElementMiddle( Element* el, Element* parent );

	/*!
	 * \brief
	 *
	 * \param
	 *
	 * \return
	 */
	void alignElementCenter( Element* el, Element* parent );

public:

		/*!
	 * \brief
	 *
	 * \param
	 *
	 * \return
	 */
	GUIFactory(SDL_Window* window);

		/*!
	 * \brief
	 *
	 * \param
	 *
	 * \return
	 */
	virtual ~GUIFactory();

		/*!
	 * \brief
	 *
	 * \param
	 *
	 * \return
	 */
	GUIManager* newGUIManager( const char* xmlFile );


};






#endif