// Shell on 22.08.2019
#version 330 core 
//------------------------------------------------------------------------------
// position	  	= Dummy
//------------------------------------------------------------------------------

layout (location=0) in vec4 position;

void main()
{
    // 4th attribute aPos.w is for perspective division
    gl_Position         = position;
    // we're setting position through gl_position var for next step
}
