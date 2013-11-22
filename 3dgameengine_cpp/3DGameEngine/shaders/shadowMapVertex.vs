#version 330

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texCoord;
layout (location = 2) in vec3 normal;

uniform mat4 transformProjected;

out vec2 texCoord0;

void main()
{
	gl_Position = transformProjected * vec4(position, 1.0);
	texCoord0 = texCoord;
}