#include "glrenderer.h"

#include <vector>

#include "commonTypes.h"
#include "logging.h"
#include "fileio.h"

local GLuint CreateGLProgram(const char* vertex_file_path, const char* fragment_file_path) {
    
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
    
	glDetachShader(ProgramID, VertexShaderID);
	glDetachShader(ProgramID, FragmentShaderID);
    
	glDeleteShader(VertexShaderID);
	glDeleteShader(FragmentShaderID);
    
	return ProgramID;
}

GLMeshInfo GLRenderInit(char *vertexShaderLocation, char *fragmentShaderLocation) {
    // #BADA55
    glClearColor(0.729f, 0.854f, 0.333f, 1.0f);
    
    GLMeshInfo result = {0};
    
    GLuint programID = CreateGLProgram(vertexShaderLocation, fragmentShaderLocation);
    result.programID = programID;
    
    GLfloat vertices[]{
        -1.0f, -1.0f, 0.0f,
        1.0f, -1.0f, 0.0f,
        0.0f, 1.0f,  0.0f
    };
    result.numVertices = 3;
    result.drawMode = GL_TRIANGLES;
    
    //Create Vertex Array Object and bind to it
    GLuint vao;
    glGenVertexArrays(1, &vao);
    result.vao = vao;
    glBindVertexArray(vao);
    
    //Create vertex buffer object
    GLuint vbo;
    glGenBuffers(1, &vbo);
    //Bind the vertex buffer object
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    //Turn our vbo into an array buffer
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices),
                 vertices, GL_STATIC_DRAW);
    
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    
    return result;
}

// NOTE(Adin): It's up to the platform layer to swap buffers becasue that
// varies between platforms
void GLRender(GLMeshInfo meshInfo) {
    //Begin frame
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	//Get VAA ready for draw
    glBindVertexArray(meshInfo.vao);
	//Bind to the given program
	glUseProgram(meshInfo.programID);
	
    //Draw a triangle
	glDrawArrays(meshInfo.drawMode, 0, meshInfo.numVertices);
    
	//Unbind objects
    glUseProgram(0);
    glBindVertexArray(0);
}