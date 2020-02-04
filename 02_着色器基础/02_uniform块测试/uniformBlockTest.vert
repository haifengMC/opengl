#version 430

uniform vPos
{
	vec4 pos;
	vec4 color;
};

void main()
{
	gl_Position = pos;
}