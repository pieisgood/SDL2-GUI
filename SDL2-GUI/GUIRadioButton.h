/**
 * \class GUIRadioButton
 *
 * \ingroup SDL2-GUI
 *
 * \brief A derived radio button class
 *
 * This class is used to create and handle radio buttons
 *
 * \note Should be built by a factory
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

#ifndef GUI_RADIO_BUTTON
#define GUI_RADIO_BUTTON
#include"Element.h"

namespace SDLGUI {

class GUIRadioButton : public Element {
private:
	bool m_state; /*<! If true, our Radio button has been clicked, if false it has not been clicked */

public:
	GUIRadioButton();
	~GUIRadioButton();


	/*!
	 * \brief draws the Radio button
	 */
	virtual void draw();

	/*!
	 * \brief May need to be deleted as it does not serve a purpose
	 */
	virtual void onClick();

	/*!
	 * \brief Used to check whether the mouse is over the current element
	 *
	 * \param x The x position of the mouse
	 * \param y The y position of the mouse
	 *
	 * \return True if the mouse is over the element, false otherwise.
	 */
	virtual bool isOver( int x, int y );

	/*!
	 * \brief Handles mouse motions, should be overridden
	 *
	 * \param ev An sdl_event that should be a mouse motion event
	 *
	 */
	virtual void onMouseMotion( SDL_Event* ev );

	/*!
	 * \brief Handles mouse button clicked events
	 *
	 * \param ev An sdl_event that should be a mouse button event
	 * \param clicked A GUIEvent reference that will be filled in when the GUIManager handles a button event
	 */
	virtual void onMouseButton( SDL_Event* ev, std::shared_ptr<GUIEvent> clicked );

};

}

#endif