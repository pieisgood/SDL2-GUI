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

		Element* newElement( tinyxml2::XMLElement* type, Element* parent );
		Element* newButton(int x, int y, int width, int height, const char* id, Element* parent, const char* texture, glm::vec2 scale);
		Element* newLayout(int x, int y, int width, int height, const char* id, Element* parent, glm::vec2 scale);
		Element* newTextBox( int x, int y, int width, int height, const char* id, Element* parent, glm::vec2 scale, std::string text, GUIView* view);
		Element* handleButton(tinyxml2::XMLElement* buttonElement, Element* parent);
		Element* handleLayout(tinyxml2::XMLElement* layoutElement, Element* parent);
		GUIFont* newGUIFont(const char* fontTexture , const char* fontData , GLSLProgram* fontProgram);


		unsigned char* loadImage(const char* file, int* x, int* y);

		void iterateTree( tinyxml2::XMLElement* node, Element* parent);

		GLuint newTexture(const char* file);

		GLSLProgram* newProgram( const char* vertShader, const char* fragShader);

		glm::vec2 getPos( float x, float y );

	public:

		GUIFactory(SDL_Window* window);
		virtual ~GUIFactory();

		GUIManager* newGUIManager( const char* xmlFile );


};






#endif