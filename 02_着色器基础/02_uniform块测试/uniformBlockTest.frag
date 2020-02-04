#version 430

out vec4 fColor;

uniform vPos
{
	vec4 pos;
	vec4 color;
};

void main()
{
	fColor = color;
}