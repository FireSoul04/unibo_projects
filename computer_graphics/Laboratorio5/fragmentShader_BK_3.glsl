#version 330 core

out vec4 FragColor;

uniform vec2 iResolution;
uniform float iTime;

void main()
{
    // Normalizza coordinate pixel in [0,1]
    vec2 uv = gl_FragCoord.xy / iResolution.xy;

    // Crea uno spostamento orizzontale oscillante nel tempo
    float wave = sin(10.0 * uv.x + iTime * 3.0);

    // Calcola un pattern di bande verticali colorate oscillanti
    float bands = smoothstep(0.0, 0.1, fract(uv.y * 10.0 + wave));

    // Colori di base: da blu a ciano
    vec3 color1 = vec3(0.0, 0.5, 1.0);
    vec3 color2 = vec3(0.0, 1.0, 0.5);

    // Interpola i colori in base alle bande
    vec3 color = mix(color1, color2, bands);

    FragColor = vec4(color, 1.0);
}