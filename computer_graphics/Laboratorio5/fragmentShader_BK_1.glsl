#version 330 core

out vec4 FragColor;
uniform vec2 iResolution; // Risoluzione della finestra (in pixel)
uniform float iTime;      // Tempo trascorso (in secondi)

void main() {
    // Coordinate normalizzate del frammento [0,1]
    vec2 st = vec2(0.1, 0.0) + gl_FragCoord.xy / iResolution.xy;
    
    // Creiamo un pattern che ripete 10 bande orizzontali usando fract
    // Moltiplichiamo la coordinata verticale per 10, poi estraiamo la parte frazionaria
    float bands = fract((st.y * st.y) / st.x * 10.0);
    
    // Colore basato sulla banda, crea un gradiente da nero a bianco su ogni banda
    vec3 color = vec3(bands);
    
    gl_FragColor = vec4(color, 1.0);
}