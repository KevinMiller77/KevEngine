#version 330

uniform float rotAngle;

layout(location = 0) in vec3 vertexPosition_modelspace;

void main(){
    gl_Position = vec4(vertexPosition_modelspace, 1) * mat4x4(vec4(cos(rotAngle), 0, sin(rotAngle), 0),
                                                              vec4(0, 1, 0, 0),
                                                              vec4(-sin(rotAngle), 0, cos(rotAngle), 0),
                                                              vec4(0, 0, 0, 1));
}