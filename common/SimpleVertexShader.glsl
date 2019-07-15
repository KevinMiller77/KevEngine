#version 130
in vec3 vertexPosition_modelspace;

void main(){
    vec3 pos = vertexPosition_modelspace;
    gl_Position.xyz = pos;
    gl_Position.w = 1.0;
}