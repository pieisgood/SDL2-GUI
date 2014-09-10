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
#include <memory>
#include <iostream>
#include <fstream>
#include "GUIManager.h"
#include "tinyxml2.h"

namespace SDLGUI {

class GUIFactory {
private:
		tinyxml2::XMLDocument* m_doc; //our XML document
		std::shared_ptr<GUIView> m_view;
		std::shared_ptr<GUIManager> m_manager;
		int m_windowWidth;
		int m_windowHeight;

	/*!
	 * \brief
	 *
	 * \param
	 *
	 * \return
	 */
	std::shared_ptr<Element> newElement( tinyxml2::XMLElement* type, std::shared_ptr<Element> parent );

	/*!
	 * \brief
	 *
	 * \param
	 *
	 * \return
	 */
	std::shared_ptr<Element> newButton(int x, int y, int width, int height, const char* id, std::shared_ptr<Element> parent, const char* texture, glm::vec2 scale);

	/*!
	 * \brief
	 *
	 * \param
	 *
	 * \return
	 */
	std::shared_ptr<Element> newLayout(int x, int y, int width, int height, const char* id, std::shared_ptr<Element> parent, glm::vec2 scale);

	/*!
	 * \brief
	 *
	 * \param
	 *
	 * \return
	 */
	std::shared_ptr<Element> newTextBox( int x, int y, int width, int height, const char* id, std::shared_ptr<Element> parent, glm::vec2 scale, std::string text, std::shared_ptr<GUIView> view);

	/*!
	 * \brief
	 *
	 * \param
	 *
	 * \return
	 */
	std::shared_ptr<Element> handleButton(tinyxml2::XMLElement* buttonElement, std::shared_ptr<Element> parent);

	/*!
	 * \brief
	 *
	 * \param
	 *
	 * \return
	 */
	std::shared_ptr<Element> handleLayout(tinyxml2::XMLElement* layoutElement, std::shared_ptr<Element> parent);

	/*!
	 * \brief
	 *
	 * \param
	 *
	 * \return
	 */
	std::shared_ptr<GUIFont> newGUIFont(const char* fontTexture , const char* fontData , std::shared_ptr<GLSLProgram> fontProgram);

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
	void iterateTree( tinyxml2::XMLElement* node, std::shared_ptr<Element> parent);

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
	std::shared_ptr<GLSLProgram> newProgram( const char* vertShader, const char* fragShader);

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
	glm::vec4 createStencil( std::shared_ptr<Element> el, std::shared_ptr<Element> parent );

	/*!
	 * \brief
	 *
	 * \param
	 *
	 * \return
	 */
	void alignElementLeft( std::shared_ptr<Element> el, std::shared_ptr<Element> parent );

	/*!
	 * \brief
	 *
	 * \param
	 *
	 * \return
	 */
	void alignElementRight( std::shared_ptr<Element> el, std::shared_ptr<Element> parent );

	/*!
	 * \brief
	 *
	 * \param
	 *
	 * \return
	 */
	void alignElementMiddle( std::shared_ptr<Element> el, std::shared_ptr<Element> parent );

	/*!
	 * \brief
	 *
	 * \param
	 *
	 * \return
	 */
	void alignElementCenter( std::shared_ptr<Element> el, std::shared_ptr<Element> parent );

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
	std::shared_ptr<GUIManager> newGUIManager( const char* xmlFile );


};


}



#endif