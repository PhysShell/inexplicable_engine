// Shell on 22.08.2019
#version 330 core 
//------------------------------------------------------------------------------
// outputColor	  	    = output for fragment
// fragmentColor        = input from the vertex shader
//------------------------------------------------------------------------------
smooth  in  vec4 fragmentColor;
        out vec4 outputColor;
        
void main()
{
    // float y             = gl_FragCoord.y/640.0f;
    //                  the greater the y, the darker
    // outputColor         = mix(vec4(1.0f,1.0f,1.0f,1.0f),vec4(.2f,.2f,.2f,1.0f),y);
    outputColor             = fragmentColor;
}
