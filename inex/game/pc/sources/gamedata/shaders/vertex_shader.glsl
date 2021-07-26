// Shell on 22.08.2019
#version 330 core 
//------------------------------------------------------------------------------
// position	  	= input specifying the data of zero attribute 
// color        = input specifying color
// fragmentColor= output specifying color being passed in color
//------------------------------------------------------------------------------

layout (location=0) in vec4 position;
layout (location=1) in vec4 color;
smooth              out vec4 fragmentColor;

void main()
{
    gl_Position         = position;
    fragmentColor       = color;
}
