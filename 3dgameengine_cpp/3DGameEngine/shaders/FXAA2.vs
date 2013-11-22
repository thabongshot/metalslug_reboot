#version 330

#define FXAA_SUBPIX_SHIFT (1.0 / 4.0)

layout (location = 0) in vec3 Position;

out vec4 uv;
out vec2 rcpFrame0;

uniform vec2 rcpFrame;

void main()
{
	gl_Position = vec4(Position, 1.0f);
	
	vec4 result;
	result.xy = (Position.xy * 0.5) + 0.5;
	result.zw = result.xy - (rcpFrame * (0.5 + FXAA_SUBPIX_SHIFT));
	uv = result;
	
	rcpFrame0 = rcpFrame;
}