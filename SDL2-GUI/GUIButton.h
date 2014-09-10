/**
 * \class GUI2DButton
 *
 * \ingroup SDL2-GUI
 *
 * \brief A derived button class
 *
 * This class implements an HTML Button Element.
 * A texture can be provided to override the default button design.
 * Buttons can have any size or position in their parent Element.
 * 
 *
 * \note Allows for clickable buttons
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

#ifndef SDLGUIBUTTON
#define SDLGUIBUTTON
#include "Element.h"
#include <glm\glm.hpp>

namespace SDLGUI {

class GUI2DButton : public Element {
private:
	friend class GUIFactory;

	const char* m_id; /*!< The id string that represents this button */
	GLuint m_subRoutine; /*!< The shader subroutine used for highlighting the button */
	GLuint m_textureId; /*!< The texture that we use to render the button */


protected:

	void assignWidth(float width){
		m_width = width;
	}

	void assignHeight(float height){
		m_height = height;
	}

	void assignPosition(glm::vec2 pos){
		m_pos = pos;
	}

	void assignId(const char* id){
		m_id = id;
	}

	void assignTexture(GLuint textureId){
		m_textureId = textureId;
	}

	void assignScale( glm::vec2 scale) {
		m_scale = scale;
	}

public:

	/*!
	 * \brief
	 *
	 * \param
	 *
	 * \return
	 */
	GUI2DButton();

	/*!
	 * \brief
	 *
	 * \param
	 *
	 * \return
	 */
	virtual ~GUI2DButton();

	/*!
	 * \brief
	 *
	 * \param
	 *
	 * \return
	 */
	virtual void draw();

	/*!
	 * \brief
	 *
	 * \param
	 *
	 * \return
	 */
	virtual void onClick();

	/*!
	 * \brief
	 *
	 * \param
	 *
	 * \return
	 */
	virtual bool isOver(int x, int y);

	/*!
	 * \brief
	 *
	 * \param
	 *
	 * \return
	 */
	virtual void onMouseMotion(SDL_Event* ev);

	/*!
	 * \brief
	 *
	 * \param
	 *
	 * \return
	 */
	virtual void onMouseButton(SDL_Event* ev, std::shared_ptr<GUIEvent> clicked);

	/*!
	 * \brief
	 *
	 * \param
	 *
	 * \return
	 */
	virtual void onMouseScroll(SDL_Event* ev);

};

}

#endif