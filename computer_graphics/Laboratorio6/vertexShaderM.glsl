#version 330 core

// Attributi comuni Figura/Curva
layout(location = 0) in vec3 aPos;      // posizione dei vertici
layout(location = 1) in vec4 aColor;    // colore dei vertici
 

// Attributi extra solo per Curva (control points, facoltativi)
layout(location = 2) in vec3 cp;        // punto di controllo
layout(location = 3) in vec4 cpColor;   // colore del punto di controllo

// Uniform per distinguere fra Figura e Curva
uniform mat4 Projection, Model;
uniform vec4 colorA;  // Colore di partenza (es. centro)
uniform vec4 colorB;  // Colore di destinazione (es. bordo)

out vec4 ourColor;

vec3 pos;
vec4 col;

void main()
{
	pos = aPos;
       ourColor = aColor;

    gl_Position = Projection * Model * vec4(pos, 1.0);

    
}
	
