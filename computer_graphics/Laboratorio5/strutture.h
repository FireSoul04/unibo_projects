/*
#pragma once //: È una direttiva che indica al compilatore di includere il file una sola volta per unità di compilazione.
//  Il meccanismo esatto varia a seconda del compilatore, ma in generale si basa su un meccanismo interno per tenere traccia dei file già inclusi.
//Non è parte dello standard C++, quindi la sua disponibilità e il comportamento preciso possono variare tra diversi compilatori. Tuttavia, è supportata dalla maggior parte dei compilatori moderni.
*/


#pragma once

#include "lib.h"

enum Forma {
    BACKGROUND=0,
    FARFALLA = 1,
    CUORE=2
};

typedef struct {
    GLuint VAO;  //identificatore del  Vertex Array Object (VAO)
    GLuint  VBO_vertices; //identificatore del  Vertex Buffer Object (VBO) che contiene le coordinate dei vertici dell'oggetto.
    GLuint  VBO_colors;   // l'identificatore del VBO che contiene i colori dei vertici dell'oggetto.
    int nTriangles;  // numero di triangoli che costituiscono l'oggetto.
    // vertices
    vector<vec3> vertices;  //vector che contiene le coordinate dei vertici dell'oggetto. Ogni elemento del vettore è un vec3, che rappresenta una posizione 3D (x, y, z).
    vector<vec4> colors; //vector che contiene i colori dei vertici dell'oggetto. Ogni elemento del vettore è un vec4, che rappresenta un colore RGBA (red, green, blue, alpha).
    // Numero vertices  
    int nv;  //Numero di vertici della figura geometrica
    int render; //specifica come devono essere interpretati i vertici  nella fase di rendering
    mat4 Model; //Matrice di Modellazione associata alla figura che posizione l'oggetto nel mondo
    vec3 position;  //Posizione in coordinate del mondo
    vec3 scale;  //scala
    float rotation;
    unsigned int shader_programId; // Identificatore del programma shader associato all'oggetto per il rendering.
    vec4 min_BB_obj;// Coordinate del corner inferiore sinistro del Bounding Box dell'oggetto, definite nel sistema di riferimento locale.
    vec4 max_BB_obj;// Coordinate del corner superiore destro del Bounding Box dell'oggetto, definite nel sistema di riferimento locale.
    vec4 min_BB_w; // Coordinate del corner inferiore sinistro del Bounding Box dell'oggetto, trasformate nel sistema di riferimento del mondo.
    vec4 max_BB_w;// Coordinate del corner superiore destro del Bounding Box dell'oggetto, trasformate nel sistema di riferimento del mondo.
    float timerFig;
    bool isalive;
} Figura;  

