#include"Element.h"

namespace SDLGUI {

Element::~Element(){

}

void Element::addChild( std::shared_ptr<Element> child ){
	m_children.push_back(child);
}

void Element::addBound( std::shared_ptr<GUIBound> bound ){
	m_boundary = bound;
}

void Element::addParent( std::shared_ptr<Element> parent ){
	m_parent = parent;
}

}