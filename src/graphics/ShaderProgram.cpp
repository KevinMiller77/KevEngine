#include "ShaderProgram.h"

GLuint CreateGLProgram(const char* vertex_file_path, const char* fragment_file_path) {
    
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
    
	glDetachShader(ProgramID, VertexShaderID);
	glDetachShader(ProgramID, FragmentShaderID);
    
	glDeleteShader(VertexShaderID);
	glDeleteShader(FragmentShaderID);
    
	return ProgramID;
}

GLuint getShaderUniformLocation(GLuint shaderProgramID, const GLchar* name)
{
	return glGetUniformLocation(shaderProgramID, name);
}

void setShaderUniform1f(GLuint shaderProgramID, const GLchar* name, float value)
{
	glUniform1f(getShaderUniformLocation(shaderProgramID, name), value);
}

void setShaderUniform1i(GLuint shaderProgramID, const GLchar* name, int value)
{
	glUniform1i(getShaderUniformLocation(shaderProgramID, name), value);
}

void setShaderUniform2f(GLuint shaderProgramID, const GLchar* name, const Vec2& vector)
{
	glUniform2f(getShaderUniformLocation(shaderProgramID, name), vector.x, vector.y);
}

void setShaderUniform3f(GLuint shaderProgramID, const GLchar* name, const Vec3& vector)
{
	glUniform3f(getShaderUniformLocation(shaderProgramID, name), vector.x, vector.y, vector.z);
}

void setShaderUniform4f(GLuint shaderProgramID, const GLchar* name, const Vec4& vector)
{
	glUniform4f(getShaderUniformLocation(shaderProgramID, name), vector.x, vector.y, vector.z, vector.w);
}

void setShaderUniformMat4(GLuint shaderProgramID, const GLchar* name, const Mat4& matrix)
{
	glUniformMatrix4fv(getShaderUniformLocation(shaderProgramID, name), 1, GL_FALSE, matrix.elements);
}

void enableShaderProgram(GLuint shaderProgramID)
{
	glUseProgram(shaderProgramID);
}

void disableShaderProgram()
{
	glUseProgram(0);
}