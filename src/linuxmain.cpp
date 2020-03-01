#if 0
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <sstream>
#include <vector>
#include <X11/Xlib.h>
#include <string>
#define GLEW_STATIC
#include <GL/glew.h>
#include <GL/glx.h>
#include "commonTypes.h"
#include "math.h"


struct PlatformState {
Display                 *dpy;
Window                  root;
XVisualInfo             *vi;
Colormap                cmap;
XSetWindowAttributes    swa;
Window                  win;
GLXContext              glc;
XWindowAttributes       gwa;
XEvent                  xev;
};


void render(GLuint ShaderProgramID, GLfloat *vertexArray, GLenum mode, int dimensions);
GLuint loadShaders(const char *vertex_file_path, const char *fragment_file_path);

int main (int argc, char* argv[]){

    //Initialize platform state variables
    PlatformState ps;
    GLint att[] = { GLX_RGBA, GLX_DEPTH_SIZE, 24, GLX_DOUBLEBUFFER, None };

    ps.dpy = XOpenDisplay(NULL);

    //Ensure ability to open display
    if (ps.dpy == NULL){
        LOGE("Cannot connect to X server!\n");
        exit(0);
    } 
    //Find desktop window
    ps.root = DefaultRootWindow(ps.dpy);
    //Grab the visual info
    ps.vi = glXChooseVisual(ps.dpy, 0, att);

    //Check that visual info is available
    if(ps.vi == NULL){
        printf("\n\tNo appropriate visual found!\n\n");
        exit(0);
    }
    else {
        printf("\n\tVisual %p Selected\n", (void *)ps.vi->visualid);
    }

    ps.cmap = XCreateColormap(ps.dpy, ps.root, ps.vi->visual, AllocNone);

    //Set the colormap and eventmask
    ps.swa.colormap = ps.cmap;
    ps.swa.event_mask = ExposureMask | KeyPressMask;

    //Create a window on top of the desktop
    ps.win = XCreateWindow( ps.dpy, ps.root, 0, 0, 1280, 720, 0, 
                            ps.vi->depth, InputOutput, ps.vi->visual,
                            CWColormap | CWEventMask, &ps.swa);
    
    //Show the window and give it a name`
    XMapWindow(ps.dpy, ps.win);
    XStoreName(ps.dpy, ps.win, "TLETC Test Window");

    //Create context and assign it to the current context`
    ps.glc = glXCreateContext(ps.dpy, ps.vi, NULL, GL_TRUE);
    glXMakeCurrent(ps.dpy, ps.win, ps.glc);


    //Enable openGL
    glEnable(GL_DEPTH_TEST);

    //Enable higher glsl versions
    glewExperimental = GL_TRUE;

    //Enable GLEW
    GLenum err = glewInit();
    if (err != GLEW_OK){
        printf("\nGLEW could not init! Program will now end!\n");
        return 1;
    }
    printf("GLEW Enabled on version : %s\n", glewGetString(GLEW_VERSION));
    printf("GL Functions grabbed on version : %s\n", glGetString(GL_VERSION));
    //Load shaders before entering loop
    GLuint programID = loadShaders("shaders/SimpleVertexShader.glsl", "shaders/SimpleFragShader.glsl");

    GLfloat vertices[] {
        -1.0f, -1.0f, 0.0f,
         1.0f, -1.0f, 0.0f,
         0.0f, 1.0f,  0.0f
    };

	glClearColor(1.0f, 0.0f, 1.0f, 0.0f);

	//Create Vertex Array Object and bind to it
	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	//Create vertex buffer object
	GLuint vbo;
	glGenBuffers(1, &vbo);
	//Bind the vertex buffer object
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	//Turn our vbo into an array buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(vao),
	vao, GL_STATIC_DRAW);

    //Start the running loop
    bool running = true;
    while(running){
        //Check for current event
        XNextEvent(ps.dpy, &ps.xev);

        //If window is exposed continue drawing
        if(ps.xev.type == Expose){
            XGetWindowAttributes(ps.dpy, ps.win, &ps.gwa);
            glViewport(0, 0, ps.gwa.width, ps.gwa.height);
            render(programID, vertices, vbo, GL_TRIANGLES, 3);
            glXSwapBuffers(ps.dpy, ps.win);
        }

        //If button is pressed destroy the window
        else if (ps.xev.type == KeyPress) {
            glXMakeCurrent(ps.dpy, None, NULL);
            glXDestroyContext(ps.dpy, ps.glc);
            XDestroyWindow(ps.dpy, ps.win);
            XCloseDisplay(ps.dpy);
            running = false;
            exit(0);
        }
    }

    return 0;
}

GLuint loadShaders(const char *vertex_file_path, const char *fragment_file_path){
    
    //Create the shaders
    GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
    GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

    //Grab vertex shader info from file
    std::string VertexShaderCode;
    std::ifstream VertexShaderStream(vertex_file_path, std::ifstream::in);
    if(VertexShaderStream.is_open()){
        std::stringstream sstr;
        sstr << VertexShaderStream.rdbuf();
        VertexShaderCode = sstr.str();
        VertexShaderStream.close();
    } else {
        printf("Could not open vertex shader file. Are you in the right dir?\n");
        getchar();
        return 0;
    }

    //Grab fragment shader info from file
    std::string FragmentShaderCode;
    std::ifstream FragmentShaderStream(fragment_file_path, std::ifstream::in);
    if(FragmentShaderStream.is_open()){
        std::stringstream sstr;
        sstr << FragmentShaderStream.rdbuf();
        FragmentShaderCode = sstr.str();
        FragmentShaderStream.close();
    } else {
        printf("Could not open fragment shader file. Are you in the right dir?\n");
        getchar();
        return 0;
    }

    GLint Result = GL_FALSE;
    int InfoLogLength;

    //Compile vertex shader
    printf("Compiling shader : %s\n", vertex_file_path);
    char const * VertexShaderPointer = VertexShaderCode.c_str();
    glShaderSource(VertexShaderID, 1, &VertexShaderPointer, NULL);
    glCompileShader(VertexShaderID);

    //Check the Compile
    glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
    glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if (InfoLogLength > 0){
        std::vector<char> VertexShaderErrorMessage(InfoLogLength + 1);
        glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
        printf("%s\n", &VertexShaderErrorMessage[0]);
    }

    //Compile fragment shader
    printf("Compiling shader : %s\n", fragment_file_path);
    char const * FragmentShaderPointer = FragmentShaderCode.c_str();
    glShaderSource(FragmentShaderID, 1, &FragmentShaderPointer, NULL);
    glCompileShader(FragmentShaderID);

    //Check the Compile
    glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
    glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if (InfoLogLength > 0){
        std::vector<char> FragmentShaderErrorMessage(InfoLogLength + 1);
        glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
        printf("%s\n", &FragmentShaderErrorMessage[0]);
    }

    printf("Linking program!\n");
    GLuint ProgramID = glCreateProgram();
    glAttachShader(ProgramID, VertexShaderID);
    glAttachShader(ProgramID, FragmentShaderID);
    glLinkProgram(ProgramID);

    //Check the program
    glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
    glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if (InfoLogLength > 0){
        std::vector<char> ProgramErrorMessage(InfoLogLength + 1);
        glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
        printf("%s\n", &ProgramErrorMessage[0]);
    }

    glDetachShader(ProgramID, VertexShaderID);
    glDetachShader(ProgramID, FragmentShaderID);

    glDeleteShader(VertexShaderID);
    glDeleteShader(FragmentShaderID);

    return ProgramID;
}


void render(GLuint ShaderProgramID, GLuint vertexBuffer, GLenum mode, int dimensions) { 

	//Draw background
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Get VAA ready for draw
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	//Bind to the given shader state
	glUseProgram(ShaderProgramID);
	//Draw a triangle
	glDrawArrays(mode, 0, dimensions);

	glDisableVertexAttribArray(0);
}
#endif