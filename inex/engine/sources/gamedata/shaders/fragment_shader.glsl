// Shell on 22.08.2019
#version 330 core 
//------------------------------------------------------------------------------
// outputColor	  	    = output for fragment
//------------------------------------------------------------------------------
out vec4 outputColor;
        
void main()
{
    // float y             = gl_FragCoord.y/640.0f;
    //                  the greater the y, the darker
    // outputColor         = mix(vec4(1.0f,1.0f,1.0f,1.0f),vec4(.2f,.2f,.2f,1.0f),y);
    outputColor             = vec4(1.f,1.f,1.f,1.f);
}
