#version 330 core

out vec4 FragColor;
uniform vec2 iResolution;

void main()
{
//La variabile GLSL gl_FragCoord rappresenta le coordinate del frammento (ossia del pixel) nello spazio finestra (window space), ed è un vettore a 4 componenti: (x, y, z, w). 
//In particolare:
//gl_FragCoord.x e gl_FragCoord.y sono le coordinate del pixel corrente rispetto all'origine della finestra, che si trova nell'angolo in basso a sinistra. 
//Quindi, gl_FragCoord.x //varia da 0 fino alla larghezza in pixel della viewport.
//FragCoord.z è la profondità del frammento nel buffer di profondità.
//gl_FragCoord.w è il valore di omogeneizzazione.
  

    float u = gl_FragCoord.x / iResolution.x; //dividendo la posizione reale x (numero di pixel da sinistra) per la larghezza totale della finestra in pixel (iResolution.x)
                                              //il risultato è valore compreso tra 0 e 1 che indica la posizione orizzontale del frammento rispetto alla larghezza totale dello                            					      // schermo 

    vec3 leftColor = vec3(1.0, 0.0, 1.0);
    vec3 rightColor = vec3(1.0, 1.0, 0.0);

    FragColor = vec4(mix(leftColor, rightColor, u), 1.0); //effettua l'interpolazione lineare tra i due colori  (la sfumatura del colore) in base alla posizione
}