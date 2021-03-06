#version 460 core

subroutine vec4 LightFunc(vec3);

subroutine (LightFunc) vec4 ambient(vec3 n)
{
	return Materials.ambient;
}
subroutine (LightFunc) vec4 diffuse(vec3 n)
{
	return Materials.diffuse * max(dot(normalize(n), LightVec.xyz), 0.0);
}
subroutine uniform LightFunc materialShader;

void main()
{

}