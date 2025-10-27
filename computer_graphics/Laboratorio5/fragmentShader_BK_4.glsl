#version 330 core

out vec4 FragColor;
in vec2 FragCoord; // Coordinate pixel per pixel passate dal vertex shader (in pixels)
uniform vec2 iResolution; // Risoluzione della finestra (larghezza, altezza)

float circle(vec2 uv, vec2 center, float radius) {
    return smoothstep(radius, radius - 0.01, length(uv - center));
}

void main() {
    // Coordinate normalizzate da 0 a 1
    vec2 uv = gl_FragCoord.xy / iResolution.xy;

    // Spostiamo l’origine (0,0) in basso a sinistra e limitiamo al 30% in altezza (fiori solo in basso)
    if (uv.y > 0.3) {
        discard; // Niente fiori sopra il 30% verticale
    }

    // Numero di fiori da disegnare orizzontalmente
    int numFlowers = 2;

    // Calcolo la posizione orizzontale del fiore corrente (con ripetizione)
    float flowerSpacing = 1.0 / float(numFlowers);
    int flowerIndex = int(uv.x / flowerSpacing);
    float flowerX = flowerSpacing * (float(flowerIndex) + 0.5);

    // Posizione del centro del fiore (y fisso poco sopra il bordo inferiore)
    vec2 flowerCenter = vec2(flowerX, 0.15);

    // Calcolo offset locale per il fiore (coordinate del pixel nel sistema fiore)
    vec2 localPos = uv - flowerCenter;

    // Colori dei petali e centro
    vec3 petalColor = vec3(1.0, 0.5, 0.7);   // Rosa chiaro
    vec3 centerColor = vec3(1.0, 0.9, 0.3);  // Giallo

    // Disegno 5 petali: cerchi spostati attorno al centro
    float petalRadius = 0.06;
    float centerRadius = 0.05;

    float petalMask = 0.0;

    // Angoli dei petali a 72 gradi (5 petali)
    for (int i = 0; i < 5; i++) {
        float angle = radians(72.0 * float(i));
        vec2 petalCenter = flowerCenter + vec2(cos(angle), sin(angle)) * 0.07;
        petalMask += circle(uv, petalCenter, petalRadius);
    }

    // Cerchio centrale
    float centerMask = circle(uv, flowerCenter, centerRadius);

    // Composizione finale: il colore è petalo o centro, con sfondo verde
    vec3 bgColor = vec3(0.2, 0.6, 0.2); // Verde prato

    vec3 color = mix(bgColor, petalColor, min(petalMask, 1.0));
    color = mix(color, centerColor, centerMask);

    FragColor = vec4(color, 1.0);
}