#include "ShaderProgram.h"

ShaderProgram::ShaderProgram(const char* vertex_file_path, const char* fragment_file_path)
{
	programID = CreateGLProgram(vertex_file_path, fragment_file_path);
}

GLuint ShaderProgram::CreateGLProgram(const char* vertex_file_path, const char* fragment_file_path) {
    
	//Create the shaders
	GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
    
	//Grab vertex shader info from file
	FileContents vertexShader = ReadFileContents(vertex_file_path);
	if(!vertexShader.length) {
        LOG(ERR, "Could not open vertex shader file. Are you in the right dir?\n");
        DestroyFileContents(vertexShader);
        return 0;
	}
    
	//Grab fragment shader info from file
    FileContents fragmentShader = ReadFileContents(fragment_file_path);
	if(!fragmentShader.length) {
        LOG(ERR, "Could not open fragment shader file. Are you in the right dir?\n");
        DestroyFileContents(vertexShader);
        DestroyFileContents(fragmentShader);
        return 0;
	}
    
	GLint Result = GL_FALSE;
	int InfoLogLength;
    
	//Compile vertex shader
	LOG(INF, "Compiling shader: \"%s\"\n", vertex_file_path);
	const char *VertexShaderPointer = (const char *)vertexShader.data;
	glShaderSource(VertexShaderID, 1, &VertexShaderPointer, NULL);
	glCompileShader(VertexShaderID);
    
	//Check the Compile
	glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
        std::vector<char> VertexShaderErrorMessage(InfoLogLength + 1);
        glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
        LOG(ERR, "%s\n", &VertexShaderErrorMessage[0]);
	}
    
	//Compile fragment shader
	LOG(INF, "Compiling shader: \"%s\"\n", fragment_file_path);
	const char *FragmentShaderPointer = (const char *)fragmentShader.data;
	glShaderSource(FragmentShaderID, 1, &FragmentShaderPointer, NULL);
	glCompileShader(FragmentShaderID);
    
	//Check the Compile
	glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
        std::vector<char> FragmentShaderErrorMessage(InfoLogLength + 1);
        glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
        LOG(ERR, "%s\n", &FragmentShaderErrorMessage[0]);
	}
    
    //Cleanup file memory
    DestroyFileContents(vertexShader);
    DestroyFileContents(fragmentShader);
    
	LOG(INF, "Linking program!\n");
	GLuint ProgramID = glCreateProgram();
	glAttachShader(ProgramID, VertexShaderID);
	glAttachShader(ProgramID, FragmentShaderID);
	glLinkProgram(ProgramID);
    
	//Check the program
	glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
	glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
        std::vector<char> ProgramErrorMessage(InfoLogLength + 1);
        glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
        LOG(ERR, "%s\n", &ProgramErrorMessage[0]);
	}
    
    glValidateProgram(ProgramID);
    
	//glDetachShader(ProgramID, VertexShaderID);
	//glDetachShader(ProgramID, FragmentShaderID);
    
	glDeleteShader(VertexShaderID);
	glDeleteShader(FragmentShaderID);
    
	return ProgramID;
}

GLuint ShaderProgram::getShaderUniformLocation(GLuint shaderProgramID, const GLchar* name)
{
	GLint oldID;
	glGetIntegerv(GL_CURRENT_PROGRAM,&oldID);

	glUseProgram(shaderProgramID);
	GLuint out = glGetUniformLocation(shaderProgramID, name);
	glUseProgram(oldID);
	
	return out;
}


void   ShaderProgram::setUniform1f(const GLchar* name, float value)
{
	setShaderUniform1f(programID, name, value);
}

void  ShaderProgram::setUniform1fv(const GLchar* name, float* value, GLsizei count)
{
	glUniform1fv(getUniformLocation(name), count, value);
}

void   ShaderProgram::setUniform1i(const GLchar* name, int value)
{
	setShaderUniform1i(programID, name, value);
}


void   ShaderProgram::setUniform1iv(const GLchar* name, int* value, GLsizei count)
{
	glUniform1iv(getUniformLocation(name), count, value);
}
void   ShaderProgram::setUniform2f(const GLchar* name, const Vec2f& vector)
{
	setShaderUniform2f(programID, name, vector);
}

void   ShaderProgram::setUniform3f(const GLchar* name, const Vec3f& vector)
{
	setShaderUniform3f(programID, name, vector);
}

void   ShaderProgram::setUniform4f(const GLchar* name, const Vec4f& vector)
{
	setShaderUniform4f(programID, name, vector);
}

void   ShaderProgram::setUniformMat4(const GLchar* name, const Mat4f& matrix)
{
	setShaderUniformMat4(programID, name, matrix);
}

GLuint ShaderProgram::getUniformLocation(const GLchar* name)
{
	return getShaderUniformLocation(programID, name);
}

void   ShaderProgram::enable()
{
	enableShaderProgram(programID);
}

void   ShaderProgram::disable()
{
	disableShaderProgram();
}

void ShaderProgram::setShaderUniform1f(GLuint shaderProgramID, const GLchar* name, float value)
{
	glUniform1f(getShaderUniformLocation(shaderProgramID, name), value);
}

void ShaderProgram::setShaderUniform1i(GLuint shaderProgramID, const GLchar* name, int value)
{
	glUniform1i(getShaderUniformLocation(shaderProgramID, name), value);
}

void ShaderProgram::setShaderUniform2f(GLuint shaderProgramID, const GLchar* name, const Vec2f& vector)
{
	glUniform2f(getShaderUniformLocation(shaderProgramID, name), vector.x, vector.y);
}

void ShaderProgram::setShaderUniform3f(GLuint shaderProgramID, const GLchar* name, const Vec3f& vector)
{
	glUniform3f(getShaderUniformLocation(shaderProgramID, name), vector.x, vector.y, vector.z);
}

void ShaderProgram::setShaderUniform4f(GLuint shaderProgramID, const GLchar* name, const Vec4f& vector)
{
	glUniform4f(getShaderUniformLocation(shaderProgramID, name), vector.x, vector.y, vector.z, vector.w);
}

void ShaderProgram::setShaderUniformMat4(GLuint shaderProgramID, const GLchar* name, const Mat4f& matrix)
{
	glUniformMatrix4fv(getShaderUniformLocation(shaderProgramID, name), 1, GL_FALSE, matrix.elements);
}

void ShaderProgram::enableShaderProgram(GLuint shaderProgramID)
{
	glUseProgram(shaderProgramID);
}

void ShaderProgram::disableShaderProgram()
{
	glUseProgram(0);
}