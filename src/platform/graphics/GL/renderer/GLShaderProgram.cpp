#include <platform/graphics/GL/renderer/GLShaderProgram.h>

#include <glad/glad.h>

GLShaderProgram::GLShaderProgram(const char* vertex_file_path, const char* fragment_file_path)
{
	programID = CreateGLProgram(vertex_file_path, fragment_file_path);
}

unsigned int GLShaderProgram::CreateGLProgram(const char* vertex_file_path, const char* fragment_file_path) {
    
	//Create the shaders
	unsigned int VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	unsigned int FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
    
	LOG_INF("Getting first file\n");

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
    
	int Result = GL_FALSE;
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
	unsigned int ProgramID = glCreateProgram();
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

unsigned int GLShaderProgram::RefreshGLProgram(const char* vertex_file_path, const char* fragment_file_path) {

    //Create the shaders
    unsigned int VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
    unsigned int FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

    LOG_INF("Getting first file\n");

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

    int Result = GL_FALSE;
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
    unsigned int ProgramID = programID;
    glDeleteShader(VertexShaderID);
    glDeleteShader(FragmentShaderID);
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
}

//unsigned int GLShaderProgram::GetShaderUniformLocation(unsigned int shaderProgramID, const char* name)
//{
//	int oldID;
//	glGetIntegerv(GL_CURRENT_PROGRAM,&oldID);
//
//	glUseProgram(shaderProgramID);
//	unsigned int out = glGetUniformLocation(shaderProgramID, name);
//	glUseProgram(oldID);
//
//	return out;
//}
//
//
//void   GLShaderProgram::SetUniform1f(const char* name, float value)
//{
//	SetShaderUniform1f(programID, name, value);
//}
//
//void  GLShaderProgram::SetUniform1fv(const char* name, float* value, int count)
//{
//	glUniform1fv(GetUniformLocation(name), count, value);
//}
//
//void   GLShaderProgram::SetUniform1i(const char* name, int value)
//{
//	SetShaderUniform1i(programID, name, value);
//}
//
//
//void   GLShaderProgram::SetUniform1iv(const char* name, int* value, int count)
//{
//	glUniform1iv(GetUniformLocation(name), count, value);
//}
//void   GLShaderProgram::SetUniform2f(const char* name, const Vec2f& vector)
//{
//	SetShaderUniform2f(programID, name, vector);
//}
//
//void   GLShaderProgram::SetUniform3f(const char* name, const Vec3f& vector)
//{
//	SetShaderUniform3f(programID, name, vector);
//}
//
//void   GLShaderProgram::SetUniform4f(const char* name, const Vec4f& vector)
//{
//	SetShaderUniform4f(programID, name, vector);
//}
//
//void   GLShaderProgram::SetUniformMat4(const char* name, const Mat4f& matrix)
//{
//	SetShaderUniformMat4(programID, name, matrix);
//}
//
//unsigned int GLShaderProgram::GetUniformLocation(const char* name)
//{
//	return GetShaderUniformLocation(programID, name);
//}
//
void   GLShaderProgram::Enable()
{
    glUseProgram(programID);
}

void   GLShaderProgram::Disable()
{
    glUseProgram(0);
}
//
//void GLShaderProgram::SetShaderUniform1f(unsigned int shaderProgramID, const char* name, float value)
//{
//	glUniform1f(GetShaderUniformLocation(shaderProgramID, name), value);
//}
//
//void GLShaderProgram::SetShaderUniform1i(unsigned int shaderProgramID, const char* name, int value)
//{
//	glUniform1i(GetShaderUniformLocation(shaderProgramID, name), value);
//}
//
//void GLShaderProgram::SetShaderUniform2f(unsigned int shaderProgramID, const char* name, const Vec2f& vector)
//{
//	glUniform2f(GetShaderUniformLocation(shaderProgramID, name), vector.x, vector.y);
//}
//
//void GLShaderProgram::SetShaderUniform3f(unsigned int shaderProgramID, const char* name, const Vec3f& vector)
//{
//	glUniform3f(GetShaderUniformLocation(shaderProgramID, name), vector.x, vector.y, vector.z);
//}
//
//void GLShaderProgram::SetShaderUniform4f(unsigned int shaderProgramID, const char* name, const Vec4f& vector)
//{
//	glUniform4f(GetShaderUniformLocation(shaderProgramID, name), vector.x, vector.y, vector.z, vector.w);
//}
//
//void GLShaderProgram::SetShaderUniformMat4(unsigned int shaderProgramID, const char* name, const Mat4f& matrix)
//{
//	glUniformMatrix4fv(GetShaderUniformLocation(shaderProgramID, name), 1, GL_FALSE, matrix.elements);
//}
//
//void GLShaderProgram::EnableShaderProgram(unsigned int shaderProgramID)
//{
//	glUseProgram(shaderProgramID);
//}
//
//void GLShaderProgram::DisableShaderProgram()
//{
//	glUseProgram(0);
//}
