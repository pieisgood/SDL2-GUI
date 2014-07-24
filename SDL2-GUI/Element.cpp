#include"Element.h"

Element::~Element(){

}

void Element::addChild( Element* child ){
	m_children.push_back(child);
}

void Element::addBound(GUIBound* bound){
	m_boundary = bound;
}

void Element::addParent( Element* parent ){
	m_parent = parent;
}
