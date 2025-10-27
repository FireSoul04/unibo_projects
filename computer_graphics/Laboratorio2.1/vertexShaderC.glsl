#version 330 core // Versione GLSL utilizzata

// Attributo di input: posizione del vertice (vec3, coordinate x,y,z)
// 'layout(location = 0)' lega questa variabile alla location 0 del buffer dei dati del vertice.
// 'in' significa che questa variabile riceve dati in ingresso per ogni vertice.

layout(location = 0) in vec3 aPos;

// Attributo di input: colore del vertice (vec4, RGBA)
// Legato alla location 1 del buffer dati.
layout(location = 1) in vec4 Color;

// Variabile di output verso il fragment shader.
// Viene interpolata e passata per ogni pixel che compone il triangolo.
out vec4 colore_frag;

void main() {
    // gl_Position è una variabile built-in di tipo vec4 nel vertex shader.
    // Essa contiene la posizione finale del vertice nello spazio delle coordinate normalizzate.
    //
    // La GPU usa gl_Position per sapere dove disegnare il vertice sullo schermo,
    // applicando successivamente la divisione prospettica e il viewport transform.
    //
    // Qui la posizione viene passata direttamente senza trasformazioni.

    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);

    // Passa il colore ricevuto dal buffer dati all'output verso il fragment shader,
    // così che poi venga interpolato e utilizzato per colorare ogni frammento.

    colore_frag = Color;
}


