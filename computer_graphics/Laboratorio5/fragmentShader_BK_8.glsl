#version 330 core
 
in vec4 ourColor;
uniform vec2 iResolution;
out vec4 FragColor;
uniform float iTime;

void main()
{
	if (gl_FragCoord.x < 400)
		FragColor = vec4(1, 0, 0, 1);
	else
		FragColor = vec4(0, 1, 0, 1);
}

