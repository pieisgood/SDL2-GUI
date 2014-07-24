/**
 * \class GUIBound
 *
 * \ingroup SDL2-GUI
 *
 * \brief Base class for boudning geometry
 *
 * This class is the base class for all boudning objects.
 * Each derived class should represent a single geometric bound.
 * Each derived class should only expose the isHit() member function.
 * 
 *
 * \note All bounding objects must derive from this class
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

#ifndef GUIBOUND
#define GUIBOUND
#include <glm\glm.hpp>

class GUIBound {

public:

		/*!
	 * \brief
	 *
	 * \param
	 *
	 * \return
	 */
	GUIBound(){};

		/*!
	 * \brief
	 *
	 * \param
	 *
	 * \return
	 */
	virtual ~GUIBound(){};


		/*!
	 * \brief
	 *
	 * \param
	 *
	 * \return
	 */
	virtual bool isHit( float mouse_x, float mouse_y ) = 0;

};

#endif