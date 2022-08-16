#version 430

layout(location=0) in vec3 vertexPosition;
layout(location=2) in vec2 vertexUV;

uniform mat4 uModel;
uniform mat4 uView;
uniform mat4 uProjection;

out vec2 UV;

void main()
{

	gl_Position = uProjection * uView * uModel * vec4(vertexPosition, 1.0f);
	UV = vertexUV;

}
