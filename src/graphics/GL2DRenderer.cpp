#include "GL2DRenderer.h"

void Win32Render(HDC windowHDC, GLMeshInfo meshInfo) {
    //Begin frame
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
    GLRenderMesh(meshInfo);
    
    //End frame and display
    SwapBuffers(windowHDC);
}

void GLRenderMesh(GLMeshInfo meshInfo) {
	//Get VAA ready for draw
    glBindVertexArray(meshInfo.vao);
    //Bind to the given program
	glUseProgram(meshInfo.programID);
    
    //Draw the mesh
    glDrawArrays(meshInfo.drawMode, 0, meshInfo.numElements);
    
    //Unbind objects
    glUseProgram(0);
    glBindVertexArray(0);
}
