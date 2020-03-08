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

#include "TLETC.h"


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

TLETC *tletc = nullptr;

void render(GLuint ShaderProgramID, GLfloat *vertexArray, GLenum mode, int dimensions);
GLuint loadShaders(const char *vertex_file_path, const char *fragment_file_path);
bool restartContext();
bool toggleFullscreen();

int main (int argc, char* argv[]){

    //Initialize platform state variables
    PlatformState ps;
    GLint att[] = { GLX_RGBA, GLX_DEPTH_SIZE, 24, GLX_DOUBLEBUFFER, None };

    ps.dpy = XOpenDisplay(NULL);

    //Ensure ability to open display
    if (ps.dpy == NULL){
        LOG_ERR("Cannot connect to X server!\n");
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

    tletc = new TLETC(Vec2u(960, 540));
    tletc->restartContext = restartContext;
    tletc->toggleFullScreen = toggleFullscreen;

    tletc->OnGameStart();

    //Start the running loop
    bool running = true;
    while(true){
        //Check for current event
        if (XCheckMaskEvent(ps.dpy, 5, &ps.xev))
        {
            if (ps.xev.type == Expose)
            {
                LOG_INF("Exposed");
            }

            //If button is pressed destroy the window
            if (ps.xev.type == KeyPress) {

                InputInformation state;
                switch (ps.xev.xbutton.button)
                {
                    case 0:
                        break;

                    case 0xA:
                    case 0xB:
                    case 0xC:
                    case 0xD:
                    case 0xE:
                    case 0xF:
                    case 0x10:
                    case 0x11:
                    case 0x12:
                        state._key = ps.xev.xbutton.button - 0x9 + 0x30;
                        tletc->ProcessInput(state);
                        break;
                    case 0x13:
                        state._key = 0x30;
                        tletc->ProcessInput(state);
                        break;
                        



                    case 0x1B:
                        state._key = 0x52;
                        tletc->ProcessInput(state);
                        break;

                    default:
                        LOG_INF("Indientified button pressed: 0x%x", ps.xev.xbutton.button);
                        break;
                }

#if 0
                glXMakeCurrent(ps.dpy, None, NULL);
                glXDestroyContext(ps.dpy, ps.glc);
                XDestroyWindow(ps.dpy, ps.win);
                XCloseDisplay(ps.dpy);
                running = false;
                exit(0);
#endif
            }
        }


            tletc->Update();
            tletc->Draw();
            glXSwapBuffers(ps.dpy, ps.win);
    }
    
    return 0;
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

bool restartContext()
{
    LOG_ERR("Cant restart on linux yet!\n");
    return false;
}

bool toggleFullscreen()
{
    void glutFullScreen();
    return true;
}