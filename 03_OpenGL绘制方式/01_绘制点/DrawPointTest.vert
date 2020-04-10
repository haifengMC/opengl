#version 460 core

layout (location = 0) in float pointSize;

void main()
{
	gl_PointSize = pointSize;
	gl_Position = vec4(0.0, 0.0, 0.0, 1.0);
}