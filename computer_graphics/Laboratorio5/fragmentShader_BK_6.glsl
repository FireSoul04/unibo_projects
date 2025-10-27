#version 330 core

out vec4 FragColor;
 

uniform vec2 iResolution;
uniform float iTime;

float rand(vec2 co) {
    return fract(sin(dot(co.xy, vec2(12.9898,78.233))) * 43758.5453123);
}

float triangleShape(vec2 uv, float xPos, float baseWidth, float baseY, float height) {
    if (uv.y < baseY || uv.y > (baseY + height)) return 0.0;
    float distX = abs(uv.x - xPos);
    float currentBase = baseWidth * (1.0 - (uv.y - baseY) / height);
    return smoothstep(currentBase, currentBase * 0.9, distX);
}

float rectShape(vec2 uv, float xPos, float width, float baseY, float height) {
    if (uv.y < baseY || uv.y > (baseY + height)) return 0.0;
    float distX = abs(uv.x - xPos);
    return smoothstep(width, width * 0.9, distX);
}

void main() {
    vec2 uv = gl_FragCoord.xy / iResolution.xy;

    // 1. Calcolo e disegno cielo tempestoso per tutta la metà superiore
    vec3 skyColor = mix(vec3(0.6, 0.85, 1.0), vec3(0.1, 0.5, 0.9), max(0.0, (uv.y - 0.5) * 2.0));
    float seed = rand(uv * 100.0);
    float cloudLayer = smoothstep(0.3, 0.0, length(uv - vec2(0.5, 0.7 + 0.2 * sin(seed))));
    skyColor = mix(skyColor, vec3(0.3, 0.3, 0.3), cloudLayer);

    float flicker = step(0.95, fract(iTime + seed));
    float lightning = flicker * smoothstep(0.1, 0.0, abs(uv.y - 0.85 + 0.05 * sin(iTime * 10.0 + seed * 100.0)));
    skyColor += vec3(1.0, 1.0, 0.8) * lightning;

    // 2. Base prato verde visibile solo nella metà inferiore
    vec3 grassColor = vec3(0.05, 0.25, 0.05);

    vec3 color = uv.y > 0.5 ? skyColor : grassColor;

    // 3. Disegno alberi (tronco e chioma)
    int numTrees = 8;
    for (int i = 0; i < numTrees; i++) {
        float xPos = float(i) / float(numTrees - 1);
        float treeHeight = 0.2 + 0.15 * sin(xPos * 15.0 + iTime);
        float trunkHeight = treeHeight * 0.3;
        float canopyHeight = treeHeight * 0.7;
        float baseY = 0.4; // parte bassa degli alberi

        float trunkWidth = 0.02;
        float canopyBaseWidth = 0.12;

        float trunkMask = rectShape(uv, xPos, trunkWidth, baseY, trunkHeight);
        float canopyMask = triangleShape(uv, xPos, canopyBaseWidth, baseY + trunkHeight, canopyHeight);

        vec3 trunkColor = vec3(0.36, 0.25, 0.20);
        vec3 canopyColor = vec3(0.0, 0.5, 0.15);

        // Mix con blending corretto
        color = mix(color, trunkColor, trunkMask);
        color = mix(color, canopyColor, canopyMask);
    }

    FragColor = vec4(color, 1.0);
}
