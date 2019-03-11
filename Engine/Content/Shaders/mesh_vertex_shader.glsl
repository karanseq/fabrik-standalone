// GLSL shaders require the version to be #defined before anything else in the shader
#version 420

// Input
//======

layout(location = 0) in vec3 i_position;
layout(location = 1) in vec4 i_color;

uniform mat4 g_camera_view;
uniform mat4 g_world_camera;
uniform mat4 g_model_world;

// Output
//=======

layout(location = 0) out vec4 o_color;

// Entry Point
//============

void main()
{
	gl_Position = g_camera_view * g_world_camera * g_model_world * vec4(i_position, 1.0);
	o_color = i_color;
}
