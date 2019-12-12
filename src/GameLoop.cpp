#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <GL/glew.h>
#include <GL/wglew.h>

#include "CommonTypes.h"

#include "utils/Logging.h"
#include "utils/FileIO.h"

#include "graphics/Renderable2D.h"
#include "graphics/GL2DRenderer.h"

//GLMeshInfo tempMesh = {0};

// GL2DRenderer renderer;
// GLuint programID = 0;
Renderable2D* sprite1 = nullptr;
GL2DRenderer* renderer = nullptr;
//Call that happens every time the game starts
void OnGameStart(){
    // #BADA55
    glClearColor(0.729f, 0.854f, 0.333f, 1.0f);
    
    
#if 0
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
#else

    renderer = new GL2DRenderer();

    Mat4 ortho = Mat4::orthographic(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f);

    GLuint programID = CreateGLProgram("../shaders/SimpleVertexShader.glsl", "../shaders/SimpleFragShader.glsl");
	enableShaderProgram(programID);
	setShaderUniformMat4(programID, "pr_matrix", ortho);
	setShaderUniformMat4(programID, "ml_matrix", Mat4::translation(Vec3(0, 0, 0)));

    setShaderUniform2f(programID, "light_pos", Vec2(4.0f, 1.5f));
	setShaderUniform4f(programID, "colour", Vec4(0.2f, 0.3f, 0.8f, 1.0f));

    sprite1 = new Renderable2D("Item1", Vec3(0.0f, 0.0f , 0.0f), Vec2(1.0f, 1.0f), Vec4(0.5f, 0.0f, 5.0f, 1.0f), programID);
    
    //LOG_INF("Sprite 1 programID: %s\n", programID);

    renderer->submit(sprite1);

#endif
}

//Code that is called directly before each frame is drawn
void Draw(HDC windowHDC)
{
    // Sample render function to show where to put rendering code
    Win32Render(windowHDC, renderer);
}

void Update()
{
    Vec3 newPos = sprite1->getPosition();
    if (newPos.x > 16)
    {
        newPos.x = 0.0f;
    } 
    else
    {
        newPos.x += 1.0f;
    }
    sprite1->setPosition(newPos);


    renderer->submit(sprite1);
}