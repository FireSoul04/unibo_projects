#version 330 core


// Attributi extra solo per Curva (control points, facoltativi)
layout(location = 0) in vec3 aPos;        // coordinate dei vertici
layout(location = 6) in float aT;   // colore del punto di controllo

uniform mat4 Projection, Model;
uniform vec4 colorA;  // Colore di partenza (es. centro)
uniform vec4 colorB;  // Colore di destinazione (es. bordo)

out vec4 ourColor;

void main()
{
    gl_Position = Projection * Model * vec4(aPos, 1.0);
    ourColor=mix(colorA,colorB,aT);
    
}
	
