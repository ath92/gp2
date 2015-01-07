#version 120
#extension GL_EXT_geometry_shader4 : enable
#extension GL_EXT_gpu_shader4 : enable

uniform float pointSize;
uniform float screenSize;

const float PI = 3.1415926;

void main(void){
    float offset = 5 * length(gl_BackColorIn[0].xy);
    vec4 offsetx = vec4(offset, 0, 0, 0);
    vec4 offsety = vec4(0, offset, 0, 0);

    gl_Position = gl_PositionIn[0];
    gl_FrontColor = gl_FrontColorIn[0];
    EmitVertex();

    gl_Position = gl_PositionIn[0]+offsetx;
    gl_FrontColor = gl_FrontColorIn[0];
    EmitVertex();

    gl_Position = gl_PositionIn[0]+offsety;
    gl_FrontColor = gl_FrontColorIn[0];
    EmitVertex();

    EndPrimitive();
    
}