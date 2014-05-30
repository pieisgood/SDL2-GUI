#include"GUIFactory.h"
#include"stb_image.h"

GUIFactory::GUIFactory(SDL_Window* window) {
	SDL_GetWindowSize(window, &m_windowWidth, &m_windowHeight);
};

GUIFactory::~GUIFactory(){

};

GUIManager* GUIFactory::newGUIManager( const char* xmlFile ){
	m_doc = new tinyxml2::XMLDocument();

	GLSLProgram* program = this->newProgram( "panel.vert", "panel.frag" );
	GLSLProgram* textProgram = this->newProgram( "text.vert", "text.frag" );
	m_view = new GUIView( program );
	m_view->assignFont( this->newGUIFont("C:\\Users\\Lee\\Documents\\Visual Studio 2012\\Projects\\SDL2-GUI\\SDL2-GUI\\content\\Fonts\\VeraMoBI.ttf_sdf.png", "C:\\Users\\Lee\\Documents\\Visual Studio 2012\\Projects\\SDL2-GUI\\SDL2-GUI\\content\\Fonts\\VeraMoBI.txt", textProgram) );
	m_view->assignErrorTexture( newTexture("error.bmp") );
	

	m_manager = new GUIManager();
	m_manager->assignView(m_view);
	m_manager->assignProgram(program);
	m_manager->assignFPS( (GUITextBox*) newTextBox( 10, 10, 100, 100, "fps_box", NULL, glm::vec2(1.0, 1.0), "FPS: 1000", m_view) );

	if(m_doc->LoadFile(xmlFile)){
		printf("loading xml file error");
		return m_manager;
	}


	tinyxml2::XMLNode* child = m_doc->FirstChild();
	iterateTree( child->NextSiblingElement(), NULL);

	return m_manager;
}

Element* GUIFactory::newTextBox( int x, int y, int width, int height, const char* id, Element* parent, glm::vec2 scale, std::string text, GUIView* view){

	GUITextBox* outTextBox = new GUITextBox();
	outTextBox->assignView( view );
	outTextBox->assignHeight( height );
	outTextBox->assignWidth( width );
	outTextBox->addParent( parent );
	outTextBox->assignPosition( this->getPos(x + width/2, y + height/2) );
	outTextBox->assignScreenPosition( x, y );
	outTextBox->assignScale( scale );
	outTextBox->assignText( text );
	outTextBox->assignNumChars( text.size() );

	return outTextBox;
}

Element* GUIFactory::newButton(int x, int y, int width, int height, const char* id, Element* parent, const char* texture, glm::vec2 scale){

	GUI2DButton* outButton = new GUI2DButton();
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

Element* GUIFactory::newLayout(int x, int y, int width, int height, const char* id, Element* parent, glm::vec2 scale){

	GUILayout* outLayout = new GUILayout();
	outLayout->assignHeight(height);
	outLayout->assignWidth(width);
	outLayout->assignPosition( this->getPos(x + width/2, y + height/2) );
	outLayout->assignScreenPosition( x, y );
	outLayout->addParent(parent);
	outLayout->assignScale( scale );

	return outLayout;
}

GUIFont* GUIFactory::newGUIFont(const char* fontTexture , const char* fontData , GLSLProgram* fontProgram){

	GLuint textTexture = this->newTexture( fontTexture );
	GUIFont* localFont = new GUIFont( textTexture, fontData, fontProgram );

	return localFont;
}

Element* GUIFactory::newElement( tinyxml2::XMLElement* type, Element* parent ){
	const char* name = type->Name();
	if(std::strcmp( name, "button") == 0){
		float x = type->IntAttribute("width");
		float y = type->IntAttribute("height");

		Element* button = newButton( type->IntAttribute("x"), type->IntAttribute("y"),
			type->IntAttribute("width"), type->IntAttribute("height"), type->Attribute("id"),
			parent, type->Attribute("texture"), glm::vec2(x/m_windowWidth, y/m_windowHeight) );

		button->assignView(m_view);

		parent->addChild(button);

		return button;
		
	}
	else if(std::strcmp(name,"layout") == 0 ){
		float x = type->IntAttribute("width");
		float y = type->IntAttribute("height");

		Element* layout = newLayout( type->IntAttribute("x"), type->IntAttribute("y"),
			type->IntAttribute("width"), type->IntAttribute("height"), type->Attribute("id"),
			parent, glm::vec2(x/m_windowWidth, y/m_windowHeight));

		layout->assignView(m_view);

		parent->addChild(layout);

		return layout;
	}
	else if(std::strcmp(name, "text_box") == 0){
		float x = type->IntAttribute("width");
		float y = type->IntAttribute("height");

		Element* textBox = newTextBox( type->IntAttribute("x"), type->IntAttribute("y"),
			type->IntAttribute("width"), type->IntAttribute("height"), type->Attribute("id"),
			parent, glm::vec2(x, y), " ", m_view);

		textBox->assignView(m_view);

		parent->addChild(textBox);

		return textBox;
	}
	else if(std::strcmp(name,"window") == 0){
		Element* window = newLayout(0, 0 ,  m_windowWidth, m_windowHeight, "SDL_WINDOW", parent, glm::vec2(1.0, 1.0));
		m_manager->assignWindow(window);
		window->assignView(m_view);
		return window;
	}
}

void GUIFactory::iterateTree( tinyxml2::XMLElement* node, Element* parent){

	Element* element = newElement( node->ToElement(), parent);

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

GLSLProgram* GUIFactory::newProgram( const char* vertShader, const char* fragShader){
	GLSLProgram* program = new GLSLProgram();
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