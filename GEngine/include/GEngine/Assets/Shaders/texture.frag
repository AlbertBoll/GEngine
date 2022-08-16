#version 430

uniform vec3 uBaseColor;

uniform sampler2D uTexture;
//uniform sampler2DMS uTexture;

in vec2 UV;
out vec4 fragColor;

void main()
{
	vec4 color = vec4(uBaseColor, 1.f);
	
	fragColor = texture2D(uTexture, UV) ;//* vec4(uBaseColor, 1.0f);
	//fragColor = color * texture2D(uTexture, UV);
}