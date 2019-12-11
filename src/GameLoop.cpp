#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <GL/glew.h>
#include <GL/wglew.h>

#include "utils/Logging.h"
#include "utils/FileIO.h"

#include "CommonTypes.h"

GLMeshInfo tempMesh = {0};

//Call that happens every time the game starts
bool OnGameStart(){
     // #BADA55
    glClearColor(0.729f, 0.854f, 0.333f, 1.0f);
    
    tempMesh.programID = CreateGLProgram("../shaders/SimpleVertexShader.glsl", "../shaders/SimpleFragShader.glsl");
    
    GLfloat vertices[] = {
        1.0f,   7.0f,   0.0f,   //Top left
        8.0f,   1.0f,  0.0f,   //Bottom left
        15.0f,  7.0f,  0.0f   //Bottom right
    };
    tempMesh.numVertices = 4;
    
    GLushort elements[] = {
        0, 1, 2,
    };
    tempMesh.numElements = 6;
    
    tempMesh.drawMode = GL_TRIANGLES;
    
    //Create Vertex Array Object and bind to it
    GLuint vao;
    glGenVertexArrays(1, &vao);
    tempMesh.vao = vao;
    glBindVertexArray(vao);
    
    // Buffer vertices
    
    //Create vertex buffer object
    GLuint vertexBuffer;
    glGenBuffers(1, &vertexBuffer);
    //Bind the vertex buffer object
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    //Turn our vertexBuffer into an array buffer
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0); // Allways enabeled for this vao
    
    // Buffer elements
    GLuint elementBuffer;
    glGenBuffers(1, &elementBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);
    
    glBindVertexArray(0);

    return true;
}

//Code that is called directly before each frame is drawn
void Draw(HDC windowHDC){
    //If you want to change shaders, make sure to enable them before changing things


    // Sample render function to show where to put rendering code
    Win32Render(windowHDC, tempMesh);
}

void Update(){

    GLint progID = tempMesh.programID;

    glUseProgram(progID);

    float angle = ((float) (clock() % 360)) * 0.1f;
    setShaderUniform1f(progID, "rotAngle", angle);
    
    setShaderUniformMat4(progID, "pr_matrix", Mat4f::orthographic(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f));
    //setShaderUniformMat4(progID, "ml_matrix", Mat4f::translation(Vec3f(4, 3, 0)));

    setShaderUniform4f(progID, "objColor", Vec4f(0.2f, 0.5f, 0.2f, 1.0f));



    glUseProgram(0);
}