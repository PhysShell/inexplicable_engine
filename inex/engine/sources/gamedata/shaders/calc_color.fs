// Shell on 16.10.2020
#version 330

out vec4 outputColor;
uniform float fragLoopDuration;
uniform float time;

const vec4 firstColor   = vec4(1.f,1.f,1.f,1.f);
const vec4 secnodColor  = vec4(0.f,1.f,0.f,1.f);

void main()
{
    float currentTime   = mod(time,fragLoopDuration);
    float currentLerp   = currentTime/fragLoopDuration;

    outputColor         = mix(firstColor,secnodColor,currentLerp);
}