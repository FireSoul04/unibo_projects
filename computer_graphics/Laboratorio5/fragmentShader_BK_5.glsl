#version 330 core

 

out vec4 FragColor;

 
uniform vec2 iResolution; // Risoluzione della finestra
uniform float iTime;    // Tempo trascorso, per animazione


// Funzione hash semplice per randomizzare posizione orizzontale
float hash(float n) {
    return fract(sin(n) * 43758.5453123);
}

void main() {
    // Normalizza coordinate schermo (0,0 in basso a sinistra)
      vec2 uv = gl_FragCoord.xy / iResolution.xy;


    // Parametri della pioggia
    float speed = 1.5;
    float dropLength = 0.05;
    float dropWidth = 0.003;
    int numDrops = 100;

    vec3 background = vec3(0.05, 0.05, 0.1); // Colore scuro dello sfondo

    float brightness = 0.0;

    // Per ogni goccia, genera posizione casuale orizzontale e movimento verticale
    for (int i = 0; i < numDrops; i++) {
        // Posizione orizzontale randomizzata (da 0 a 1)
        float x = hash(float(i) * 12.9898);

        // Offset verticale in base al tempo (goccia che scorre verso il basso)
        float y = mod(iTime * speed + hash(float(i) * 78.233), 1.0);

        // Calcolo distanza orizzontale dal pixel corrente alla posizione della goccia
        float xDist = abs(uv.x - x);

        // Calcolo posizione verticale relativa del pixel nella goccia
        float yDist = uv.y - y;

        // Se il pixel è nello spessore orizzontale della goccia
        if (xDist < dropWidth) {
            // La goccia è una linea verticale con gradiente di luminosità lungo l’altezza
            if (yDist > 0.0 && yDist < dropLength) {
                // Intensità della luminosità decresce verso il basso della goccia
                float intensity = (dropLength - yDist) / dropLength;
                brightness = max(brightness, intensity);
            }
        }
    }

    // Colore del colore della pioggia: azzurro chiaro
    vec3 rainColor = vec3(0.7, 0.8, 1.0);

    // Combina sfondo e gocce di pioggia
    vec3 color = mix(background, rainColor, brightness);

    FragColor = vec4(color, 1.0);
}

