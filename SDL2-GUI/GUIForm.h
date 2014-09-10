/**
 * \class GUIForm
 *
 * \ingroup SDL2-GUI
 *
 * \brief An Element that handles user input requests
 *
 * This class should handle user input requests and send
 * data on these requests back to the program. This should
 * allow users to send requests and input, like user name and
 * passwords.
 *
 * \note Should be used like the HTML Form tag
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

#ifndef GUIFORM
#define GUIFORM
#include"Element.h"

namespace SDLGUI {

class GUIForm : public Element {
private:
	std::vector< std::shared_ptr<Element> > m_inputs; //the list of inputs we will recieve

public:

};

}

#endif