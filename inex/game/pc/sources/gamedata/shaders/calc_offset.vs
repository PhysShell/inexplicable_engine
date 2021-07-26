// Shell on 16.10.2020
#version 330

layout(location=0) in vec4 position;
uniform float loopDuration;
uniform float time;

void main()
{
    float timeScale     = 3.14159f*2.f/loopDuration;
    float currentTime   = mod(time,loopDuration);

    vec4 totalOffset    = vec4(
        cos(currentTime*timeScale)*.5f,
        sin(currentTime*timeScale)*.5f,
        .0f,
        .0f);

    gl_Position         = position+totalOffset;
}