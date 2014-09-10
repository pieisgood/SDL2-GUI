/**
 * \class GUIBoxBound
 *
 * \ingroup SDL2-GUI
 *
 * \brief A Bounding box object
 *
 * This class implements a bounding box.
 * 
 *
 * \note Simple bounding box
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

#ifndef GUIBOXBOUND
#define GUIBOXBOUND
#include "GUIBound.h"

namespace SDLGUI {

class GUIBoxBound : public GUIBound {
private:
	float m_width;
	float m_height;
	glm::vec2 m_pos; //top left hand point

public:
	GUIBoxBound();
	virtual ~GUIBoxBound();

	/*!
	 * \brief
	 *
	 * \param
	 *
	 * \return
	 */
	virtual bool isHit(float mouse_x, float mouse_y);

	/*!
	 * \brief
	 *
	 * \param
	 *
	 * \return
	 */
	void assignWidth(float width);

	/*!
	 * \brief
	 *
	 * \param
	 *
	 * \return
	 */
	void assignHeight(float height);

	/*!
	 * \brief
	 *
	 * \param
	 *
	 * \return
	 */
	void assignPos(glm::vec2 pos);
};

}

#endif