#pragma once
#include "strutture.h"
#include "Utilities.h"
#define PI 3.14159265358979323
extern float alpha;

void INIT_TRIANGLE(Figura* fig, vec4 color_top, vec4 color_bottom){
    fig->vertices.push_back(vec3(-0.5f, -0.5f, 0.0f));
    fig->vertices.push_back(vec3(0.5f, -0.5f, 0.0f));
    fig->vertices.push_back(vec3(0.0f, 0.5f, 0.0f));

    fig->colors.push_back(color_top);
    fig->colors.push_back(color_bottom);
    fig->colors.push_back(color_bottom);
    fig->nv = 3;
    fig->rotation = 0.0f;
    fig->render = GL_TRIANGLES;
}

void INIT_CIRCLE(float cx, float cy, float raggiox, float raggioy, Figura* fig, vec4 color_top, vec4 color_bottom) {

    int i;
    float stepA = (2 * PI) / fig->nTriangles;
    float t, xx, yy;


    fig->vertices.push_back(vec3(cx, cy, 0.0));

    fig->colors.push_back(color_top);

    for (i = 0; i <= fig->nTriangles; i++)
    {
        t = (float)i * stepA;
        xx = cx + raggiox * cos(t);
        yy = cy + raggioy * sin(t);
        fig->vertices.push_back(vec3(xx, yy, 0.0));
        //Colore 
        fig->colors.push_back(color_bottom); //Nota che la quarta componente corrisponde alla trasparenza del colore
    }

    //Calcolo AABB della figura
    findBB(fig);
    //Aggiungo al campo vertices le 4 coordinate del Bounding box in coordinate dell'oggetto
    fig->vertices.push_back(vec3(fig->min_BB_obj.x, fig->min_BB_obj.y, 0.0));
    fig->colors.push_back(vec4(1.0, 0.0, 0.0, 1.0));
    fig->vertices.push_back(vec3(fig->max_BB_obj.x, fig->min_BB_obj.y, 0.0));
    fig->colors.push_back(vec4(1.0, 0.0, 0.0, 1.0));
    fig->vertices.push_back(vec3(fig->max_BB_obj.x, fig->max_BB_obj.y, 0.0));
    fig->colors.push_back(vec4(1.0, 0.0, 0.0, 1.0));
    fig->vertices.push_back(vec3(fig->min_BB_obj.x, fig->max_BB_obj.y, 0.0));
    fig->colors.push_back(vec4(1.0, 0.0, 0.0, 1.0));


    fig->nv = fig->vertices.size();
    fig->rotation = 0.0f;
    fig->render = GL_TRIANGLE_FAN;
}

void INIT_BUTTERFLY(float cx, float cy, float raggiox, float raggioy, Figura* fig, vec4 color_top, vec4 color_bottom)
{
	int i;
	float t,xx,yy;
	float stepA = (2 * PI) / fig->nTriangles;
    fig->vertices.push_back(vec3(cx, cy, 0.0));
    

    fig->colors.push_back(color_top);

	for (i = 0; i <= fig->nTriangles; i++)
	{
		t = (float)i * stepA;
        xx = cx + raggiox * (sin(t) * (exp(cos(t)) - 2 * cos(4 * t)) + pow(sin(t / 12), 5));
        yy = cy + raggioy * (cos(t) * (exp(cos(t)) - 2 * cos(4 * t)) + pow(sin(t/ 12), 5));
        fig->vertices.push_back(vec3(xx, yy, 0.0));
        fig->colors.push_back(color_bottom);
	}
  

    //Calcolo AABB della figura
    findBB(fig);
    //Aggiungo al campo vertices le 4 coordinate del Bounding box in coordinate dell'oggetto
    fig->vertices.push_back(vec3(fig->min_BB_obj.x, fig->min_BB_obj.y, 0.0));
    fig->colors.push_back(vec4(1.0, 1.0, 1.0, 1.0));
    fig->vertices.push_back(vec3(fig->max_BB_obj.x, fig->min_BB_obj.y, 0.0));
    fig->colors.push_back(vec4(1.0, 1.0, 1.0, 1.0));
    fig->vertices.push_back(vec3(fig->max_BB_obj.x, fig->max_BB_obj.y, 0.0));
    fig->colors.push_back(vec4(1.0, 1.0, 1.0, 1.0));
    fig->vertices.push_back(vec3(fig->min_BB_obj.x, fig->max_BB_obj.y, 0.0));
    fig->colors.push_back(vec4(1.0, 1.0, 1.0, 1.0));

    fig->nv = fig->vertices.size();
    fig->render = GL_TRIANGLE_FAN;
}

void INIT_HEART(float cx, float cy, float raggiox, float raggioy, Figura* fig, vec4 color_top, vec4 color_bottom)
{
     

    int i;
    float t, xx, yy;
    float stepA = (2 * PI) / fig->nTriangles;
    fig->vertices.push_back(vec3(cx, cy, 0.0));

    fig->colors.push_back(color_top);

    for (i = 0; i <= fig->nTriangles; i++)
    {
        t = (float)i * stepA;
        xx = cx + raggiox * (16 * pow(sin(t), 3));
        yy = cy + raggioy * ((13 * cos(t) - 5 * cos(2 * t) - 2 * cos(3 * t) - cos(4 * t)));
        fig->vertices.push_back(vec3(xx, yy, 0.0));
        fig->colors.push_back(color_bottom);
    }
   
    //Calcolo AABB della figura
    findBB(fig);
    //Aggiungo al campo vertices le 4 coordinate del Bounding box in coordinate dell'oggetto
    fig->vertices.push_back(vec3(fig->min_BB_obj.x, fig->min_BB_obj.y, 0.0));
    fig->colors.push_back(vec4(1.0, 1.0, 1.0, 1.0));
    fig->vertices.push_back(vec3(fig->max_BB_obj.x, fig->min_BB_obj.y, 0.0));
    fig->colors.push_back(vec4(1.0, 1.0, 1.0, 1.0));
    fig->vertices.push_back(vec3(fig->max_BB_obj.x, fig->max_BB_obj.y, 0.0));
    fig->colors.push_back(vec4(1.0, 1.0, 1.0, 1.0));
    fig->vertices.push_back(vec3(fig->min_BB_obj.x, fig->max_BB_obj.y, 0.0));
    fig->colors.push_back(vec4(1.0, 0.0, 0.0, 1.0));
    fig->nv = fig->vertices.size();
    fig->rotation = 0.0f;
    fig->render = GL_TRIANGLE_FAN;
     
}

void INIT_PIANO(Figura* fig, vec4 color_top, vec4 color_bottom)
{
    fig->vertices.clear();

    fig->vertices.push_back(vec3(0.0, 0.0, 0.0));
    fig->colors.push_back(color_top);
    fig->vertices.push_back(vec3(1.0,0.0, 0.0));
    fig->colors.push_back(color_bottom);
    fig->vertices.push_back(vec3(1.0, 1.0, 0.0));
    fig->colors.push_back(color_top);
    fig->vertices.push_back(vec3(0.0, 1.0, 0.0));
    fig->colors.push_back(color_bottom);

    //Calcolo AABB della figura
    findBB(fig);
    //Aggiungo al campo vertices le 4 coordinate del Bounding box in coordinate dell'oggetto
    fig->vertices.push_back(vec3(fig->min_BB_obj.x, fig->min_BB_obj.y, 0.0));
    fig->colors.push_back(vec4(1.0, 1.0, 1.0, 1.0));
    fig->vertices.push_back(vec3(fig->max_BB_obj.x, fig->min_BB_obj.y, 0.0));
    fig->colors.push_back(vec4(1.0, 1.0, 1.0, 1.0));
    fig->vertices.push_back(vec3(fig->max_BB_obj.x, fig->max_BB_obj.y, 0.0));
    fig->colors.push_back(vec4(1.0, 1.0, 1.0, 1.0));
    fig->vertices.push_back(vec3(fig->min_BB_obj.x, fig->max_BB_obj.y, 0.0));
    fig->colors.push_back(vec4(1.0, 0.0, 0.0, 1.0));
    fig->nv = fig->vertices.size();
    fig->rotation = 0.0f;
    fig->render = GL_TRIANGLE_FAN;
    
    
 }

void INIT_ASTRONAVE(Figura* fig, vec4 color_top, vec4 color_bottom)
{
    
    fig->vertices.push_back(vec3(0.0f, 1.5f,0.0));
    fig->colors.push_back(color_top);
    fig->vertices.push_back(vec3(0.3f, 1.0f, 0.0));
    fig->colors.push_back(color_bottom);
    fig->vertices.push_back(vec3(0.6f, 0.5f, 0.0));
    fig->colors.push_back(color_bottom);
    fig->vertices.push_back(vec3(0.8f, 0.0f, 0.0));
    fig->colors.push_back(color_bottom);
    fig->vertices.push_back(vec3(1.0f, -0.5f, 0.0));
    fig->colors.push_back(color_bottom);
    fig->vertices.push_back(vec3(0.7f, -1.0f, 0.0));
    fig->colors.push_back(color_bottom);
    fig->vertices.push_back(vec3(0.3f, -1.2f, 0.0));
    fig->colors.push_back(color_bottom);
    fig->vertices.push_back(vec3(0.1f, -1.4f, 0.0));
    fig->colors.push_back(color_bottom);
    fig->vertices.push_back(vec3(-0.1f, -1.4f, 0.0));
    fig->colors.push_back(color_bottom);
    fig->vertices.push_back(vec3(-0.3f, -1.2f, 0.0));
    fig->colors.push_back(color_bottom);
    fig->vertices.push_back(vec3(-0.7f, -1.0f, 0.0));
    fig->colors.push_back(color_bottom);
    fig->vertices.push_back(vec3(-1.0f, -0.5f, 0.0));
    fig->colors.push_back(color_bottom);
    fig->vertices.push_back(vec3(-0.8f, 0.0f, 0.0));
    fig->colors.push_back(color_bottom);
    fig->vertices.push_back(vec3(-0.6f, 0.5f, 0.0));
    fig->colors.push_back(color_bottom);
    fig->vertices.push_back(vec3(-0.3f, 1.0f, 0.0));
    
    //Calcolo AABB della figura
    findBB(fig);
    //Aggiungo al campo vertices le 4 coordinate del Bounding box in coordinate dell'oggetto
    fig->vertices.push_back(vec3(fig->min_BB_obj.x, fig->min_BB_obj.y, 0.0));
    fig->colors.push_back(vec4(1.0, 1.0, 1.0, 1.0));
    fig->vertices.push_back(vec3(fig->max_BB_obj.x, fig->min_BB_obj.y, 0.0));
    fig->colors.push_back(vec4(1.0, 1.0, 1.0, 1.0));
    fig->vertices.push_back(vec3(fig->max_BB_obj.x, fig->max_BB_obj.y, 0.0));
    fig->colors.push_back(vec4(1.0, 1.0, 1.0, 1.0));
    fig->vertices.push_back(vec3(fig->min_BB_obj.x, fig->max_BB_obj.y, 0.0));
    fig->nv = fig->vertices.size();
    fig->rotation = 0.0f;
    fig->render = GL_TRIANGLE_FAN;


}

