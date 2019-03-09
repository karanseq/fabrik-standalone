// GLSL shaders require the version to be #defined before anything else in the shader
#version 420

// Input
//======

layout(location = 0) in vec3 i_position;
layout(location = 1) in vec4 i_color;

// Output
//=======

layout(location = 0) out vec4 o_color;

// Entry Point
//============

void main()
{
	gl_Position = vec4(i_position, 1.0);
	o_color = i_color;
}
