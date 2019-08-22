// PhysShell on 22.08.2019
#version 330 core 

layout (location=0) in vec3 aPos;

void main()
{
    // 4th attribute aPos.w is for perspective division
    gl_Position         = vec4(aPos.x,aPos.y,aPos.z,1.0);
    // we're setting position through gl_position var for next step
}