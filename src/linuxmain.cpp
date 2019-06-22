#include<stdio.h>
#include<stdlib.h>
#include<X11/Xlib.h>
#include<GL/glx.h>
#include<GL/glu.h>

struct platformState {
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

GLint att[] = { GLX_RGBA, GLX_DEPTH_SIZE, 24, GLX_DOUBLEBUFFER, None };

void DrawAQuad();

int main (int argc, char* argv[]){

    //Initialize platform state variables
    platformState ps;

    ps.dpy = XOpenDisplay(NULL);

    //Ensure ability to open display
    if (ps.dpy == NULL){
        printf("Cannot connect to X server!\n");
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
    ps.win = XCreateWindow( ps.dpy, ps.root, 0, 0, 600, 600, 0, 
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

    //Start the running loop
    bool running = true;
    while(running){
        //Check for current event
        XNextEvent(ps.dpy, &ps.xev);

        //If window is exposed continue drawing
        if(ps.xev.type == Expose){
            XGetWindowAttributes(ps.dpy, ps.win, &ps.gwa);
            glViewport(0, 0, ps.gwa.width, ps.gwa.height);
            DrawAQuad();
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

void DrawAQuad() {
 glClearColor(1.0, 1.0, 1.0, 1.0);
 glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

 glMatrixMode(GL_PROJECTION);
 glLoadIdentity();
 glOrtho(-1., 1., -1., 1., 1., 20.);

 glMatrixMode(GL_MODELVIEW);
 glLoadIdentity();
 gluLookAt(0., 0., 10., 0., 0., 0., 0., 1., 0.);

 glBegin(GL_QUADS);
  glColor3f(1., 0., 0.); glVertex3f(-.75, -.75, 0.);
  glColor3f(0., 1., 0.); glVertex3f( .75, -.75, 0.);
  glColor3f(0., 0., 1.); glVertex3f( .75,  .75, 0.);
  glColor3f(1., 1., 0.); glVertex3f(-.75,  .75, 0.);
 glEnd();
} 

