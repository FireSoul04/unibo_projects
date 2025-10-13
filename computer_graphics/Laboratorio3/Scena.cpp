#pragma once
#include <glad/glad.h>
#include "ShaderMaker.h"
#include "strutture.h"
#include "init_geometrie.h"
#include "inizializzazioni.h"

extern Figura  heart;
void costruisci_Scena(vector<Figura>* Scena)
{
 
	Figura triangle;
	//triangle.render = GL_TRIANGLES;
	INIT_TRIANGLE(&triangle, vec4(1.0, 1.0, 1.0, 1.0), vec4(1.0, 1.0, 0.0, 1.0));
	//Genera il VAO della struttura  triangolo
	INIT_VAO(&triangle);
	//Aggiunge al vector Scena la struttura di tipo Figura heart

	Figura cerchio;
	cerchio.nTriangles = 40;
	cerchio.render = GL_TRIANGLE_FAN;
	INIT_CIRCLE(-0.5, 0.5, 0.3, 0.3, &cerchio, vec4(1.0, 0.0, 0.0, 0.5), vec4(1.0, 1.0, 0.0, 0.5));
	INIT_VAO(&cerchio);

	heart.nTriangles = 40;
	heart.render = GL_TRIANGLE_FAN;
	INIT_HEART(0.5, 0.5, 0.02, 0.02, &heart, vec4(1.0, 1.0, 1.0, 0.8), vec4(0.0, 1.0, 0.5, 0.8));
	INIT_VAO_DYNAMIC(&heart);

	Figura butterfly;
	butterfly.nTriangles = 100;
	butterfly.render = GL_TRIANGLE_FAN;
	INIT_BUTTERFLY(0.6, 0.4, 0.05, 0.05, &butterfly, vec4(0.0, 1.0, 1.0, 0.4), vec4(1.0, 0.5, 0.5, 0.4));
	INIT_VAO(&butterfly);

	Scena->push_back(triangle);
	Scena->push_back(heart);
	Scena->push_back(cerchio);
	Scena->push_back(butterfly);
}

