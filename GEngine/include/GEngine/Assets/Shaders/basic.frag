#version 430

uniform vec4 uBaseColor;
uniform bool uUseVertexColor;

in vec3 color;
out vec4 fragColor;


void main()
{
	vec4 tempColor = uBaseColor; //vec4(uBaseColor, 1.0f);
	if (uUseVertexColor)
	{
		tempColor *= vec4(color, 1.0f);
	};

	fragColor = tempColor;
}