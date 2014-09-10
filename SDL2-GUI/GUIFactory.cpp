#include"GUIFactory.h"
#include"stb_image.h"

namespace SDLGUI {

GUIFactory::GUIFactory(SDL_Window* window) {
	SDL_GetWindowSize(window, &m_windowWidth, &m_windowHeight);
};

GUIFactory::~GUIFactory(){

};

std::shared_ptr<GUIManager> GUIFactory::newGUIManager( const char* xmlFile ){
	m_doc = new tinyxml2::XMLDocument();

	std::shared_ptr<GLSLProgram> program = this->newProgram( "panel.vert", "panel.frag" );
	std::shared_ptr<GLSLProgram> textProgram = this->newProgram( "text.vert", "text.frag" );
	m_view = std::shared_ptr<GUIView>(new GUIView( program ));
	m_view->assignFont( this->newGUIFont("C:\\Users\\Lee\\Documents\\Visual Studio 2012\\Projects\\SDL2-GUI\\SDL2-GUI\\content\\Fonts\\VeraMoBI.ttf_sdf.png", "C:\\Users\\Lee\\Documents\\Visual Studio 2012\\Projects\\SDL2-GUI\\SDL2-GUI\\content\\Fonts\\VeraMoBI.txt", textProgram) );
	m_view->assignErrorTexture( newTexture("error.bmp") );
	

	m_manager = std::shared_ptr<GUIManager>(new GUIManager());
	m_manager->assignView(m_view);
	m_manager->assignProgram(program);
	m_manager->assignFPS( std::static_pointer_cast<GUITextBox>(newTextBox( 100, 40, 100, 100, "fps_box", NULL, glm::vec2(1.0, 1.0), "FPS: 100000", m_view) ));

	if(m_doc->LoadFile(xmlFile)){
		printf("loading xml file error");
		return m_manager;
	}


	tinyxml2::XMLNode* child = m_doc->FirstChild();
	iterateTree( child->NextSiblingElement(), NULL);

	return m_manager;
}

std::shared_ptr<Element> GUIFactory::newTextBox( int x, int y, int width, int height, const char* id, std::shared_ptr<Element> parent, glm::vec2 scale, std::string text, std::shared_ptr<GUIView> view){

	std::shared_ptr<GUITextBox> outTextBox = std::shared_ptr<GUITextBox>(new GUITextBox());
	outTextBox->assignView( view );
	outTextBox->assignHeight( height );
	outTextBox->assignWidth( width );
	outTextBox->addParent( parent );
	outTextBox->assignPosition( this->getPos(x , y ) );
	outTextBox->assignScreenPosition( x, y );
	outTextBox->assignScale( scale );
	outTextBox->assignTextWrap( text , width );
	outTextBox->assignNumChars( text.size() );

	return outTextBox;
}

std::shared_ptr<Element> GUIFactory::newButton(int x, int y, int width, int height, const char* id, std::shared_ptr<Element> parent, const char* texture, glm::vec2 scale){

	std::shared_ptr<GUI2DButton> outButton = std::shared_ptr<GUI2DButton>(new GUI2DButton());
	outButton->assignHeight(height);
	outButton->assignWidth(width);
	outButton->assignId(id);
	outButton->addParent(parent);
	outButton->assignPosition( this->getPos(x + width/2, y + height/2) );
	outButton->assignScreenPosition( x, y );
	outButton->assignTexture( newTexture( texture ) );
	outButton->assignScale( scale );


	return outButton;
}

std::shared_ptr<Element> GUIFactory::newLayout(int x, int y, int width, int height, const char* id, std::shared_ptr<Element> parent, glm::vec2 scale){

	std::shared_ptr<GUILayout> outLayout = std::shared_ptr<GUILayout>(new GUILayout());
	outLayout->assignHeight(height);
	outLayout->assignWidth(width);
	outLayout->assignPosition( this->getPos(x + width/2, y + height/2) );
	outLayout->assignScreenPosition( x, y );
	outLayout->addParent(parent);
	outLayout->assignScale( scale );

	return outLayout;
}

std::shared_ptr<GUIFont> GUIFactory::newGUIFont(const char* fontTexture , const char* fontData , std::shared_ptr<GLSLProgram> fontProgram){

	GLuint textTexture = this->newTexture( fontTexture );
	std::shared_ptr<GUIFont> localFont = std::shared_ptr<GUIFont>(new GUIFont( textTexture, fontData, fontProgram ));

	return localFont;
}

glm::vec4 GUIFactory::createStencil( std::shared_ptr<Element> el, std::shared_ptr<Element> parent ) {
	glm::vec4 stencil; //represents the x,y position and width and height

	//need parameters defining a stencil for the element
	//also need method to obtain the stencil within the parent element
	//will need to update this down the tree

	//return created stencil, or just add to the element and make this method null
	return stencil;

}


std::shared_ptr<Element> GUIFactory::newElement( tinyxml2::XMLElement* type, std::shared_ptr<Element> parent ){
	const char* name = type->Name();
	if(std::strcmp( name, "button") == 0){
		float x = type->IntAttribute("width");
		float y = type->IntAttribute("height");

		std::shared_ptr<Element> button = newButton( type->IntAttribute("x"), type->IntAttribute("y"),
			type->IntAttribute("width"), type->IntAttribute("height"), type->Attribute("id"),
			parent, type->Attribute("texture"), glm::vec2(x/m_windowWidth, y/m_windowHeight) );

		button->assignView(m_view);

		parent->addChild(button);

		return button;
		
	}
	else if(std::strcmp(name,"layout") == 0 ){
		float x = type->IntAttribute("width");
		float y = type->IntAttribute("height");

		std::shared_ptr<Element> layout = newLayout( type->IntAttribute("x"), type->IntAttribute("y"),
			type->IntAttribute("width"), type->IntAttribute("height"), type->Attribute("id"),
			parent, glm::vec2(x/m_windowWidth, y/m_windowHeight));

		layout->assignView(m_view);

		parent->addChild(layout);

		return layout;
	}
	else if(std::strcmp(name, "text_box") == 0){
		float x = type->IntAttribute("width");
		float y = type->IntAttribute("height");
		std::string boxText = type->GetText();

		if( boxText.size() == 0 ){
			boxText.append(" ");
		}

		std::shared_ptr<Element> textBox = newTextBox( type->IntAttribute("x"), type->IntAttribute("y"),
			type->IntAttribute("width"), type->IntAttribute("height"), type->Attribute("id"),
			parent, glm::vec2(x, y), boxText , m_view);

		textBox->assignView(m_view);

		parent->addChild(textBox);

		return textBox;
	}
	else if(std::strcmp(name,"window") == 0){
		std::shared_ptr<Element> window = newLayout(0, 0 ,  m_windowWidth, m_windowHeight, "SDL_WINDOW", parent, glm::vec2(1.0, 1.0));
		m_manager->assignWindow(window);
		window->assignView(m_view);
		return window;
	}
}

void GUIFactory::iterateTree( tinyxml2::XMLElement* node, std::shared_ptr<Element> parent){

	std::shared_ptr<Element> element = newElement( node->ToElement(), parent);

	for( tinyxml2::XMLElement* loopNode = node->FirstChildElement(); loopNode != NULL; loopNode=loopNode->NextSiblingElement()){
		iterateTree(loopNode, element);
	}
}

unsigned char* GUIFactory::loadImage(const char* file, int* x, int* y){
	int n;
	int force_channels = 4;
	unsigned char* image_data = stbi_load (file, x, y, &n, force_channels);
	if (!image_data) {
	 fprintf (stderr, "ERROR: could not load %s\n", file);
	}

	// NPOT check
	if ((*x & (*x - 1)) != 0 || (*y & (*y - 1)) != 0) {
	  fprintf (
		stderr, "WARNING: texture %s is not power-of-2 dimensions\n", file
	  );
	}

	int width_in_bytes = *x * 4;
	unsigned char *top = NULL;
	unsigned char *bottom = NULL;
	unsigned char temp = 0;
	int half_height = (*y) / 2;

	for (int row = 0; row < half_height; row++) {
	  top = image_data + row * width_in_bytes;
	  bottom = image_data + (*y - row - 1) * width_in_bytes;
	  for (int col = 0; col < width_in_bytes; col++) {
		temp = *top;
		*top = *bottom;
		*bottom = temp;
		top++;
		bottom++;
	  }
	}

	return image_data;
}

GLuint GUIFactory::newTexture(const char* file){
	int x, y;
	unsigned char* image = loadImage(file, &x, &y);

	GLuint localTexture;

	glGenTextures (1, &localTexture);
	glActiveTexture (GL_TEXTURE0);
	glBindTexture (GL_TEXTURE_2D, localTexture);
	glTexImage2D (
	  GL_TEXTURE_2D,
	  0,
	  GL_RGBA,
	  x,
	  y,
	  0,
	  GL_RGBA,
	  GL_UNSIGNED_BYTE,
	  image
	);

	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	delete[](image);

	return localTexture;
}

std::shared_ptr<GLSLProgram> GUIFactory::newProgram( const char* vertShader, const char* fragShader){
	std::shared_ptr<GLSLProgram> program = std::shared_ptr<GLSLProgram>(new GLSLProgram());
	program->compileShaderFromFile(vertShader, GLSLShader::VERTEX);
	program->compileShaderFromFile(fragShader, GLSLShader::FRAGMENT);
	program->link();
	return program;
}

glm::vec2 GUIFactory::getPos( float x, float y ){
	float xPos = (2*x - (float)m_windowWidth)/(float)m_windowWidth;
	float yPos = ((float)m_windowHeight - 2*y)/(float)m_windowHeight;
	return glm::vec2(xPos, yPos);
}

}