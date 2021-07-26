// Shell on 17.11.2020
#version 400

in vec4 position;
uniform mat4 view, proj;

void main()
{
	gl_Position = proj * view * vec4 (position);
}