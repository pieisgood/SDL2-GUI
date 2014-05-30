#include"GLSLShader.h"

GLSLProgram::GLSLProgram(){
	m_handle = glCreateProgram();
	printf("%i \n", m_handle);
}

GLSLProgram::~GLSLProgram(){

}

bool GLSLProgram::compileShaderFromFile(const char* fileName, GLSLShader::GLSLShaderType type){
	if( fileExists(fileName) ){
		std::ifstream shaderStream (fileName);
		std::string shader((std::istreambuf_iterator<char>(shaderStream)), std::istreambuf_iterator<char>());
		return compileShaderFromString(shader, type);
	}
	return false;
}

bool GLSLProgram::compileShaderFromString(const std::string & source, GLSLShader::GLSLShaderType type){
	GLuint shader = 0;
	switch(type){
		case(GLSLShader::VERTEX):
			shader = glCreateShader(GL_VERTEX_SHADER);
			break;
		case(GLSLShader::FRAGMENT):
			shader = glCreateShader(GL_FRAGMENT_SHADER);
			break;
	}

	if(shader == 0){
		printf("failed to create shader");
		return false;
	}

	const char *strFileData = source.c_str();
	glShaderSource(shader, 1, &strFileData, NULL);

	glCompileShader(shader);

	GLint status;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
	if (status == GL_FALSE)
	{
		GLint infoLogLength;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);

		GLchar *strInfoLog = new GLchar[infoLogLength + 1];
		glGetShaderInfoLog(shader, infoLogLength, NULL, strInfoLog);

		const char *strShaderType = NULL;
		switch(type)
		{
		case GL_VERTEX_SHADER: strShaderType = "vertex"; break;
		case GL_GEOMETRY_SHADER: strShaderType = "geometry"; break;
		case GL_FRAGMENT_SHADER: strShaderType = "fragment"; break;
		}

		fprintf(stderr, "Compile failure in %s shader:\n%s\n", strShaderType, strInfoLog);
		delete[] strInfoLog;
		return false;
	}

	glAttachShader(m_handle, shader);

	return true;
}

bool GLSLProgram::fileExists(const std::string & fileName){
	std::ifstream f(fileName.c_str());
    if (f.good()) {
        f.close();
        return true;
    } else {
        f.close();
        return false;
    }  
}

int GLSLProgram::getUniformLocation(const char* name){
	return glGetUniformLocation(m_handle, name);
}

bool GLSLProgram::link(){
	if( m_handle == 0 ){
		printf("No program initiated \n");
		return false;
	}

	glLinkProgram( m_handle );

	GLint status;
	glGetProgramiv(m_handle, GL_LINK_STATUS, &status);

	if( GL_FALSE == status ){
		fprintf(stderr, "Failed to link shader program!\n");
		GLint loglen;
		glGetProgramiv(m_handle, GL_INFO_LOG_LENGTH, &loglen);
		if( loglen > 0 ){
			char* log = (char*)malloc(loglen);
			GLsizei written;
			glGetProgramInfoLog(m_handle, loglen, &written, log);
			fprintf(stderr, "program log: \n %s", log);
			free(log);
			return false;
		}
	}

	return true;
}

void GLSLProgram::use(){
	glUseProgram( m_handle );
}

int GLSLProgram::getHandle(){
	return m_handle;
}

bool GLSLProgram::isLinked(){
	GLint status;
	glGetProgramiv(m_handle, GL_LINK_STATUS, &status);

	if( GL_FALSE == status ){
		return false;
	}

	return true;
}

void GLSLProgram::bindAttribLocation( GLuint location, const char* name){
	glBindAttribLocation(m_handle, location, name);
}

void GLSLProgram::bindFragDataLocation(GLuint location,  const char* name){
	glBindFragDataLocation(m_handle, location, name);
}

void GLSLProgram::setUniform(const char *name, const glm::vec3 & v){
	GLuint location = glGetUniformLocation(m_handle, name);

	if( location >= 0 ){
		glUniform3f(location, v.x, v.y, v.z);
	}
}

void GLSLProgram::setUniform(const char *name, const glm::vec2 & v){
	GLuint location = glGetUniformLocation(m_handle, name);

	if( location >= 0 ){
		glUniform2f(location, v.x, v.y );
	}
}

void GLSLProgram::setUniform(const char *name, const glm::vec4 & v){
	GLuint location = glGetUniformLocation(m_handle, name);
	if( location >= 0 ){
		glUniform4f(location, v.x, v.y, v.z, v.w);
	}
}

void GLSLProgram::setUniform(const char *name, const glm::mat4 & m){
	GLuint location = glGetUniformLocation(m_handle, name);
	if( location >= 0 ){
		glUniformMatrix4fv(location, 1, GL_FALSE, &m[0][0]);
	}
}

void GLSLProgram::setUniform(const char *name, const glm::mat3 & m){
	GLuint location = glGetUniformLocation(m_handle, name);
	if( location >= 0 ){
		glUniformMatrix3fv(location, 1, GL_FALSE, &m[0][0]);
	}
}

void GLSLProgram::setUniform(const char *name, float val){
	GLuint location = glGetUniformLocation(m_handle, name);
	if( location >= 0 ){
		glUniform1f(location, val);
	}
}

void GLSLProgram::setUniform(const char *name, int val){
	GLuint location = glGetUniformLocation(m_handle, name);
	if( location >= 0 ){
		glUniform1i(location, val);
	}
}

void GLSLProgram::setUniform(const char *name, bool val){
	GLuint location = glGetUniformLocation(m_handle, name);
	if( location >= 0 ){
		glUniform1i(location, val);
	}
}

void GLSLProgram::setUniform( const char *name, float x, float y, float z, float w ){
	GLuint location = glGetUniformLocation(m_handle, name);
	if( location >= 0 ){
		glUniform4f(location, x, y, z, w);
	}
}

void GLSLProgram::setUniform(const char *name, float x, float y, float z){
	GLuint location = glGetUniformLocation(m_handle, name);
	if( location >= 0 ){
		glUniform3f(location, x, y, z);
	}
}

void GLSLProgram::setUniform(const char *name, float x, float y){
	GLuint location = glGetUniformLocation(m_handle, name);
	if( location >= 0 ){
		glUniform2f(location, x, y);
	}
}

void GLSLProgram::printActiveUniforms(){
	GLint maxLength, nUniforms;
	glGetProgramiv(m_handle, GL_ACTIVE_UNIFORMS, &nUniforms);
	glGetProgramiv(m_handle, GL_ACTIVE_UNIFORM_MAX_LENGTH, &maxLength);

	GLchar* name = (GLchar*) malloc(maxLength);

	GLint written, size, location;
	GLenum type;
	printf("Location | Name\n");
	printf("----------------------------------------------------\n");
	for( int i = 0; i < nUniforms; i++){
		glGetActiveUniform(m_handle, i, maxLength, &written, &size, &type, name);
		location = glGetUniformLocation(m_handle, name);
		printf(" %-5d | %s\n", location, name);
	}
	free(name);
}

void GLSLProgram::printActiveAttribs(){
	GLint maxLength, nAttribs;
	glGetProgramiv(m_handle, GL_ACTIVE_ATTRIBUTES, &nAttribs);
	glGetProgramiv(m_handle, GL_ACTIVE_ATTRIBUTE_MAX_LENGTH, &maxLength);

	GLchar* name = (GLchar*) malloc(maxLength);

	GLint written, size, location;
	GLenum type;
	printf("Index | Name\n");
	printf("----------------------------------------------------\n");
	for( int i = 0; i < nAttribs; i++){
		glGetActiveAttrib(m_handle, i, maxLength, &written, &size, &type, name);
		location = glGetAttribLocation(m_handle, name);
		printf(" %-5d | %s\n", location, name);
	}
	free(name);
}
