#include"GUIFont.h"
#include<iostream>
#include<sstream>
#include<vector>
#include <memory>
#include"StringUtils.h"

namespace SDLGUI {

GUIFont::GUIFont( GLuint fontTexture , const char* fontData , std::shared_ptr<GLSLProgram> fontProgram ){
	m_fontTexture = fontTexture;
	m_fontProgram = fontProgram;
	m_alpha = 1.0;
	m_color = glm::vec3(1.0,1.0,1.0);

	std::ifstream inFile(fontData);
	if( !inFile.is_open() ){
		std::cout << "FAILED TO OPEN: " << fontData << std::endl;
	}
	this->parseFont( inFile );
	inFile.close();

	
}

GUIFont::~GUIFont(){

}

void GUIFont::renderText( std::string text , float x , float y , int size ){

}

void GUIFont::renderText( GLuint textVAO , float x, float y, int size, int stringSize ){
	m_fontProgram->use();
	glBindTexture(GL_TEXTURE_2D, m_fontTexture);
	m_fontProgram->setUniform("text_pos", x, y );
	m_fontProgram->setUniform("text_color", m_color.x, m_color.y, m_color.z, m_alpha);
	glBindVertexArray(textVAO);
	glDrawArrays(GL_TRIANGLES, 0, stringSize*6);
}

void GUIFont::assignColor( glm::vec3 color ){
	m_color = color;
}

void GUIFont::assignTransparency( float alpha ){
	m_alpha = alpha;
}

GLuint GUIFont::cacheText( std::string text , GLuint vertVBO, GLuint texcoordVBO, GLuint textVAO ){

	std::vector<float> Verts;
	std::vector<float> TexCoords;
	
	this->textListFill( text, Verts, TexCoords, 0 );

	glBindVertexArray(textVAO);

		m_fontProgram->use();

			//Bind VBO to hold surface data
			glBindBuffer(GL_ARRAY_BUFFER, vertVBO);
				glBufferData(GL_ARRAY_BUFFER, sizeof(float)*Verts.size(), &Verts[0], GL_DYNAMIC_DRAW);
				//bind vertex position attribute to GLSL program
				glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, NULL);
				m_fontProgram->bindAttribLocation(0, "vert_pos");
				glEnableVertexAttribArray(0);

			//Bind VBO to hold surface data
			glBindBuffer(GL_ARRAY_BUFFER, texcoordVBO);
				glBufferData(GL_ARRAY_BUFFER, sizeof(float)*TexCoords.size(), &TexCoords[0], GL_DYNAMIC_DRAW);
				//bind texture coordinate attribute to GLSL program
				glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, NULL);
				m_fontProgram->bindAttribLocation(1, "vert_texcoord");
				glEnableVertexAttribArray(1);

		glUseProgram(0);

	glBindVertexArray(0);

	return 0;

}

GLuint GUIFont::cacheTextWrap( std::string text, GLuint vertVBO, GLuint texcoordVBO, GLuint textVAO , int width ) {

	//request GPU memory allocation of the size neccesary to hold all the vertex data in this text.
	glBindVertexArray(textVAO);

		m_fontProgram->use();

			//Bind VBO to hold surface data
			glBindBuffer(GL_ARRAY_BUFFER, vertVBO);
				glBufferData(GL_ARRAY_BUFFER, sizeof(float)*(text.size() + 1)*12, NULL , GL_DYNAMIC_DRAW);
				//bind vertex position attribute to GLSL program
				glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, NULL);
				m_fontProgram->bindAttribLocation(0, "vert_pos");
				glEnableVertexAttribArray(0);

			//Bind VBO to hold surface data
			glBindBuffer(GL_ARRAY_BUFFER, texcoordVBO);
				glBufferData(GL_ARRAY_BUFFER, sizeof(float)*(text.size() + 1)*12, NULL , GL_DYNAMIC_DRAW);
				//bind texture coordinate attribute to GLSL program
				glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, NULL);
				m_fontProgram->bindAttribLocation(1, "vert_texcoord");
				glEnableVertexAttribArray(1);

		glUseProgram(0);

	glBindVertexArray(0);


	std::vector<std::string> lines = split(text, '\n');

	std::vector<std::string>::iterator textLines = lines.begin();

	int Yoffset = 0;
	int totalText = 0;
	std::string currentLine;
	int totalWordLength = 0;
	int lineNum = 0;

	//add each line to the cached text
	for(; textLines != lines.end(); textLines++) {

		std::vector<std::string> words = split( *textLines , ' ');
		std::vector<std::string>::iterator wordList = words.begin();
		
		totalWordLength = 0;
		lineNum = 0;
		
		//add words to the cached text
		for(; wordList != words.end(); wordList++) {		

			if( currentLine.size() * m_charSet.Chars[' '].XAdvance > width ) {

				this->updateCacheText(currentLine, vertVBO, texcoordVBO, textVAO, totalText , Yoffset );

				Yoffset += m_charSet.LineHeight;
				totalText += totalWordLength;
				totalWordLength = 0;
				lineNum++;
				currentLine.clear();
			}

			totalWordLength += wordList->size();

			wordList->append(" ");
				totalWordLength += 1;

			currentLine.append(*wordList);

			
		}

		//Add last line to the cache 
		if( currentLine.size() != 0 ){
			this->updateCacheText(currentLine, vertVBO, texcoordVBO, textVAO, totalText , Yoffset );

			Yoffset += m_charSet.LineHeight;
			totalText += totalWordLength;
			lineNum++;
			currentLine.clear();
		}

		Yoffset += m_charSet.LineHeight;
	}

	return 0;
}

GLuint GUIFont::updateCacheText( std::string text, GLuint vertVBO, GLuint texcoordVBO, GLuint textVAO , int updateLocation, int CurY, int CurX ) {

	std::vector<float> vertData;
	std::vector<float> texcoordData;

	textListFill( text, vertData, texcoordData, CurY , CurX );

	glBindBuffer(GL_ARRAY_BUFFER, vertVBO);
	glBufferSubData(  GL_ARRAY_BUFFER , updateLocation*sizeof(float)*12, vertData.size()*sizeof(float), &vertData[0] );

	glBindBuffer(GL_ARRAY_BUFFER, texcoordVBO);
	glBufferSubData(  GL_ARRAY_BUFFER , updateLocation*sizeof(float)*12, texcoordData.size()*sizeof(float), &texcoordData[0] );

	return 0;
}

void GUIFont::textListFill( std::string text, std::vector<float> &Verts, std::vector<float> &TexCoords , int CurY , int CurX ) {
	const unsigned int characters = text.size();
	unsigned short CharX, CharY;
	unsigned short Width, Height;
	float OffsetX, OffsetY;
	float XAdvance;

	for( unsigned int i = 0; i < characters; ++i )
	{
		CharX = m_charSet.Chars[text[i]].x;
		CharY = m_charSet.Chars[text[i]].y;
		Width = m_charSet.Chars[text[i]].Width;
		Height = m_charSet.Chars[text[i]].Height;
		OffsetX = m_charSet.Chars[text[i]].XOffset;
		OffsetY = m_charSet.Chars[text[i]].YOffset;

		//TRIANGLE ONE
			//upper right
			TexCoords.push_back((float) (CharX+Width) / (float) m_charSet.Width);
			TexCoords.push_back((float) (m_charSet.Height - (CharY)) / (float) m_charSet.Height);
			Verts.push_back((float) (Width + CurX + OffsetX)  / 800.0f);
			Verts.push_back((float) (float)(Height - CurY) / 600.0f);
			//upper left
			TexCoords.push_back((float) CharX / (float) m_charSet.Width);
			TexCoords.push_back((float) (m_charSet.Height - (CharY)) / (float) m_charSet.Height);
			Verts.push_back((float) (CurX + OffsetX) / 800.0f );
			Verts.push_back((float) (float)(Height - CurY) / 600.0f);
			//lower left
			TexCoords.push_back((float) CharX / (float) m_charSet.Width);
			TexCoords.push_back((float) (m_charSet.Height-(CharY+Height)) / (float) m_charSet.Height);
			Verts.push_back((float) (CurX + OffsetX) / 800.0f) ;
			Verts.push_back((float) -CurY / 600.0f);

		//TRIANGLE TWO
			//lower right
			TexCoords.push_back((float) (CharX+Width) / (float) m_charSet.Width);
			TexCoords.push_back((float) (m_charSet.Height-(CharY+Height))/ (float) m_charSet.Height);
			Verts.push_back((float) (Width + CurX + OffsetX) / 800.0f);
			Verts.push_back((float)-CurY / 600.0f);
			//upper right
			TexCoords.push_back((float) (CharX+Width) / (float) m_charSet.Width);
			TexCoords.push_back((float) (m_charSet.Height - (CharY)) / (float) m_charSet.Height);
			Verts.push_back((float) (Width + CurX + OffsetX) / 800.0f );
			Verts.push_back((float) (float)(Height - CurY) / 600.0f );
			//lower left
			TexCoords.push_back((float) CharX / (float) m_charSet.Width);
			TexCoords.push_back((float) (m_charSet.Height-(CharY+Height)) / (float) m_charSet.Height);
			Verts.push_back((float) (CurX + OffsetX) / 800.0f );
			Verts.push_back((float) -CurY/ 600.0f);
			


		CurX += m_charSet.Chars[text[i]].XAdvance;
	}
}

bool GUIFont::parseFont( std::istream& Stream ) {
	std::string Line;
	std::string Read, Key, Value;
	std::size_t i;
	while( !Stream.eof() )
	{
		std::stringstream LineStream;
		std::getline( Stream, Line );
		LineStream << Line;

		//read the line's type
		LineStream >> Read;
		if( Read == "common" )
		{
			//this holds common data
			while( !LineStream.eof() )
			{
				std::stringstream Converter;
				LineStream >> Read;
				i = Read.find( '=' );
				Key = Read.substr( 0, i );
				Value = Read.substr( i + 1 );

				//assign the correct value
				Converter << Value;
				if( Key == "lineHeight" )
					Converter >> m_charSet.LineHeight;
				else if( Key == "base" )
					Converter >> m_charSet.Base;
				else if( Key == "scaleW" )
					Converter >> m_charSet.Width;
				else if( Key == "scaleH" )
					Converter >> m_charSet.Height;
				else if( Key == "pages" )
					Converter >> m_charSet.Pages;
			}
		}
		else if( Read == "char" )
		{
			//this is data for a specific char
			unsigned short CharID = 0;

			while( !LineStream.eof() )
			{
				std::stringstream Converter;
				LineStream >> Read;
				i = Read.find( '=' );
				Key = Read.substr( 0, i );
				Value = Read.substr( i + 1 );

				//assign the correct value
				Converter << Value;
				if( Key == "id" )
					Converter >> CharID;
				else if( Key == "x" )
					Converter >> m_charSet.Chars[CharID].x;
				else if( Key == "y" )
					Converter >> m_charSet.Chars[CharID].y;
				else if( Key == "width" )
					Converter >> m_charSet.Chars[CharID].Width;
				else if( Key == "height" )
					Converter >> m_charSet.Chars[CharID].Height;
				else if( Key == "xoffset" )
					Converter >> m_charSet.Chars[CharID].XOffset;
				else if( Key == "yoffset" )
					Converter >> m_charSet.Chars[CharID].YOffset;
				else if( Key == "xadvance" )
					Converter >> m_charSet.Chars[CharID].XAdvance;
				else if( Key == "page" )
					Converter >> m_charSet.Chars[CharID].Page;
			}
		}
	}

	return true;
}

}