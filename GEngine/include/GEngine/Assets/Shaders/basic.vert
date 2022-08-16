#version 430

layout(location=0) in vec3 vertexPosition;
layout(location=1) in vec3 vertexColor;

uniform mat4 uModel;
uniform mat4 uView;
uniform mat4 uProjection;


out vec3 color;

void main()
{

	gl_Position = uProjection * uView * uModel * vec4(vertexPosition, 1.0f);

	color = vertexColor;
}