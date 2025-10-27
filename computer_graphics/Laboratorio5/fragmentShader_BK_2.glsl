#version 330 core

out vec4 FragColor;

uniform vec2 iResolution;
uniform float iTime;

void main()
{
vec2 uv = gl_FragCoord.xy / iResolution.xy - 0.5;
float dist = length(uv);
float glow = pow(1.0 - dist * 2.0, 4.0); // Forte decadimento verso il bordo
float pulse = sin(iTime * 6.0) * 0.5 + 0.5; // Pulsazione oscillante da 0 a 1
vec3 neon = vec3(0.0, 1.0, 1.0);

vec3 color = mix(vec3(0.0), neon * glow, pulse);

FragColor = vec4(color, 1.0);
}