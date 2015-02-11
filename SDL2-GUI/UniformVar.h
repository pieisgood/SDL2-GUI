#ifndef GLSL_UNIFORM_VARIABLE
#define GLSL_UNIFORM_VARIABLE

#include<glm\glm.hpp>
#include<gl\glew.h>

class Uniform {
private:

public:
	Uniform( void ){}
	virtual ~Uniform( void );

	virtual void loadUniform( GLuint program ) = 0;

};


class UniformVec3 : public Uniform {

private:
	glm::vec3 m_data;
	char* m_name;

public:

	UniformVec3( void ) {};
	UniformVec3( char* name ) : m_name( name ) {}
	UniformVec3( char* name , glm::vec3 data ) : m_name( name ) , m_data( data ) {}
	~UniformVec3( void ) {};


	void setData( glm::vec3 data )  {
		m_data = data;
	}

	glm::vec3 getData( void ) {
		return m_data;
	}

	void loadUniform( GLuint program ) {

		GLuint location = glGetUniformLocation( program, (const char*) m_name );

		if( location >= 0 ){
			glUniform3f( location, m_data.x, m_data.y , m_data.z );
		}

	}

};

class UniformVec4 : public Uniform {

private:
	glm::vec4 m_data;
	unsigned char* m_name;
public:
	UniformVec4( void ) {};
	UniformVec4( unsigned char* name ) : m_name( name ) {}
	UniformVec4( unsigned char* name , glm::vec4 data ) : m_name( name ) , m_data( data ) {}
	~UniformVec4( void ) {}


	void setData( glm::vec4 data )  {
		m_data = data;
	}

	glm::vec4 getData( void ) {
		return m_data;
	}

	void loadUniform( GLuint program ) {

		GLuint location = glGetUniformLocation( program, (const char*) m_name );

		if( location >= 0 ){
			glUniform4f( location, m_data.x, m_data.y , m_data.z , m_data.w );
		}

	}


};

class UniformVec2 : public Uniform {

private:
	glm::vec2 m_data;
	unsigned char* m_name;

public:
	UniformVec2( void ) {};
	UniformVec2( unsigned char* name ) : m_name( name ) {}
	UniformVec2( unsigned char* name , glm::vec2 data ) : m_name( name ) , m_data( data ) {}
	~UniformVec2( void ) {};


	void setData( glm::vec2 data )  {
		m_data = data;
	}

	glm::vec2 getData( void ) {
		return m_data;
	}

	void loadUniform( GLuint program ) {

		GLuint location = glGetUniformLocation( program, (const char*) m_name );

		if( location >= 0 ){
			glUniform2f( location, m_data.x, m_data.y );
		}
	}


};

class UniformMat4 : public Uniform {

private:
	glm::mat4 m_data;
	unsigned char* m_name;

public:
	UniformMat4( void ) {};
	UniformMat4( unsigned char* name ) : m_name( name ) {}
	UniformMat4( unsigned char* name , glm::mat4 data ) : m_name( name ) , m_data( data ) {}
	~UniformMat4( void ) {};


	void setData( glm::mat4 data )  {
		m_data = data;
	}

	glm::mat4 getData( void ) {
		return m_data;
	}

	void loadUniform( GLuint program ) {

		GLuint location = glGetUniformLocation( program, (const char*) m_name );

		if( location >= 0 ){
			glUniformMatrix4fv(location, 1, GL_FALSE, &m_data[0][0]);
		}
	}

};

class UniformMat3 : public Uniform {

private:
	glm::mat3 m_data;
	unsigned char* m_name;

public:
	UniformMat3( void ) {};
	UniformMat3( unsigned char* name ) : m_name( name ) {}
	UniformMat3( unsigned char* name , glm::mat3 data ) : m_name( name ) , m_data( data ) {}
	~UniformMat3( void ) {};


	void setData( glm::mat3 data )  {
		m_data = data;
	}

	glm::mat3 getData( void ) {
		return m_data;
	}

	void loadUniform( GLuint program ) {

		GLuint location = glGetUniformLocation( program, (const char*) m_name );

		if( location >= 0 ){
			glUniformMatrix3fv(location, 1, GL_FALSE, &m_data[0][0]);
		}
	}


};

class UniformFloat : public Uniform {

private:
	float m_data;
	unsigned char* m_name;

public:
	UniformFloat( void ) {};
	UniformFloat( unsigned char* name ) : m_name( name ) {}
	UniformFloat( unsigned char* name , float data ) : m_name( name ) , m_data( data ) {}
	~UniformFloat( void ) {};


	void setData( float data )  {
		m_data = data;
	}

	float getData( void ) {
		return m_data;
	}

	void loadUniform( GLuint program ) {

		GLuint location = glGetUniformLocation( program, (const char*) m_name );

		if( location >= 0 ){
			glUniform1f(location, m_data);
		}
	}

};

class UniformInt : public Uniform {

private:
	int m_data;
	unsigned char* m_name;

public:
	UniformInt( void ) {};
	UniformInt( unsigned char* name ) : m_name( name ) {}
	UniformInt( unsigned char* name , int data ) : m_name( name ) , m_data( data ) {}
	~UniformInt( void ) {};


	void setData( int data )  {
		m_data = data;
	}

	int getData( void ) {
		return m_data;
	}

	void loadUniform( GLuint program ) {

		GLuint location = glGetUniformLocation( program, (const char*) m_name );

		if( location >= 0 ){
			glUniform1i(location, m_data);
		}
	}

};

class UniformBool : public Uniform {

private:
	bool m_data;
	unsigned char* m_name;

public:
	UniformBool( void ) {};
	UniformBool( unsigned char* name ) : m_name( name ) {}
	UniformBool( unsigned char* name , bool data ) : m_name( name ) , m_data( data ) {}
	~UniformBool( void ) {};


	void setData( bool data )  {
		m_data = data;
	}

	bool getData( void ) {
		return m_data;
	}

	void loadUniform( GLuint program ) {

		GLuint location = glGetUniformLocation( program, (const char*) m_name );

		if( location >= 0 ){
			glUniform1i(location, m_data);
		}
	}

};

#endif