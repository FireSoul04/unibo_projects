#pragma once
#include <glad/glad.h>
#include "ShaderMaker.h"
#include "strutture.h"
#include "init_geometrie.h"
#include "inizializzazioni.h"



extern Figura astronave, proiettile;
extern int width, height;
extern unsigned int programId, programId_BK;
void costruisci_Scena(vector<Figura>* Scena)
{
 
	
	Figura butterfly,   bkg, heart ;

	//Costruisce il piano del background
	bkg.nTriangles = 2;
	bkg.render = GL_TRIANGLE_FAN;
	bkg.shader_programId = programId_BK;
	INIT_PIANO(&bkg, vec4(0.0, 0.0, 1.0, 1.0), vec4(1.0, 1.0, 1.0, 1.0));
	INIT_VAO(&bkg);
	bkg.Model = mat4(1.0);
	bkg.Model = scale(bkg.Model, vec3((float)(width), (float)(height), 1.0));
	//Aggiunge al vector Scena la struttura di tipo Figura background
	Scena->push_back(bkg);
	
	//Costruisce i vertici del cuore: attributo posizione e color (in coordinate del sistema di riferimento dell'oggetto)
	butterfly.render = GL_TRIANGLE_FAN;
	butterfly.isalive = true;
	butterfly.nTriangles = 60;
	butterfly.timerFig = 0.0;
	butterfly.position = vec3((float(width) / 2.0), (float)(height) / 3.0,0.0);
	butterfly.scale = vec3(50.0, 50.0, 1.0);
	butterfly.shader_programId = programId;
	INIT_BUTTERFLY(0.0,0.0,0.5,0.5,&butterfly, vec4(1.0, 1.0, 1.0, 0.5), vec4(1.0, 1.0, 0.0, 0.7));
	//Genera il VAO della struttura  butterrfly
	INIT_VAO(&butterfly);
	
	//Aggiunge al vector Scena la struttura di tipo Figura Butterfly
	Scena->push_back(butterfly);
	
	//Costruisce i vertici del cuore: attributo posizione e color (in coordinate del sistema di riferimento dell'oggetto)
	heart.render = GL_TRIANGLE_FAN;
	heart.isalive = true;
	heart.nTriangles = 60;
	heart.timerFig = 0.0;
	heart.position = vec3((float(width)*0.1), (float)(height) / 3.0, 0.0);
	heart.scale = vec3(10.0, 10.0, 1.0);
	heart.shader_programId = programId;
	INIT_HEART(0.0, 0.0, 0.5, 0.5, &heart, vec4(1.0, 1.0, 1.0, 0.5), vec4(1.0, 0.0, 0.0, 0.7));
	//Genera il VAO della struttura  butterrfly
	INIT_VAO(&heart);
	Scena->push_back(heart);

	astronave.render = GL_TRIANGLE_FAN;
	astronave.shader_programId = programId;
	astronave.position = vec3((float(width) / 3.0), (float)(height)*0.1, 0.0);
	astronave.scale = vec3(100.0, 100.0, 1.0);
	INIT_ASTRONAVE(&astronave, vec4(1.0, 1.0, 1.0,0.5), vec4(0.3, 0.3, 0.3, 0.5));
	INIT_VAO(&astronave);
 

}

