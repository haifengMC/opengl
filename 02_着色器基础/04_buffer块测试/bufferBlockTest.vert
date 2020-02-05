#version 450 core

layout (binding = 0) buffer bufObj
{
	float buf;
};

void main()
{
	buf = 0.5;
	gl_Position = vec4(0.0, 0.0, 0.0, 1.0);
}