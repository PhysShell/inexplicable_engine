// Shell on 16.10.2020
#version 330

out vec4 outputColor;
uniform float fragLoopDuration;
uniform float time;

const vec4 firstColor   = vec4(1.f,1.f,1.f,1.f);
const vec4 secnodColor  = vec4(0.f,1.f,0.f,1.f);

void main()
{
    float halfw         = fragLoopDuration/2.f;
    float area          = 3.14159f/halfw;
    float innerLoop     = mod(time+halfw/2.f,halfw);

    outputColor         = vec4(sin(innerLoop*area),1.f,sin(innerLoop*area),1.f);
}