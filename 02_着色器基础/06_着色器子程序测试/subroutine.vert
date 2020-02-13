#version 460 core

layout (location = 0) in vec4 vPos;
out vec3 color;

subroutine vec3 ColorType1();
subroutine vec3 ColorType2();
subroutine vec3 ColorType3();

subroutine (ColorType1, ColorType2) vec3 ColorRed()
{
	return vec3(1.0, 0.0, 0.0);
}
subroutine (ColorType2, ColorType3) vec3 ColorGreen()
{
	return vec3(0.0, 1.0, 0.0);
}
subroutine (ColorType1, ColorType3) vec3 ColorBlue()
{
	return vec3(0.0, 0.0, 1.0);
}

subroutine uniform ColorType1 func1;
subroutine uniform ColorType2 func2;
subroutine uniform ColorType3 func3;

void main()
{
	gl_Position = vPos;
	if (vPos.x < 0)
	{
		color = func1();
	}
	else if (vPos.x == 0)
	{
		color = func2();
	}
	else
	{
		color = func3();
	}
}