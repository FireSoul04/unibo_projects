#pragma once
#include <glad/glad.h>
#include "ShaderMaker.h"
#include "strutture.h"
#include "init_geometrie.h"
#include "inizializzazioni.h"
#include "Gui.h"
#include <ImGui\imgui.h>           // Libreria core ImGui
#include <ImGui\imgui_impl_glfw.h> // Integrazione ImGui con GLFW (gestione finestra/input)
#include <ImGui\imgui_impl_opengl3.h> // Integrazione ImGui con OpenGL3 (rendering)
#include "lib.h"
#define PI 3.14159265358979323
extern int  width, height;
extern vector<Figura>Scena; 
extern ImVec4 clear_color;
 
int numCols = 6;
int numRows = 6;
double mousex, mousey; //Coordinate del mouse
float alpha;
bool flag_wireframe;

float vx = 0, vy = 0;
float px = 0, py = 0;

// Identificatori delle variabili uniformi:  Model  e Projection
extern GLuint IdProj, IdModel;
extern unsigned int programId;

extern mat4 Projection; // matrice di proiezione: dalle coordinate del mondo alle coordinate di display normalizzate


void renderizza(float currentTime){

      
    glClearColor(clear_color.x, clear_color.y, clear_color.z, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT); // Pulisce il buffer colore

    my_interface(); // Disegna l’interfaccia ImGui

    /* Renderizza la GUI ImGui */
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
 
        
     if (flag_wireframe)
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    else
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

     px = px + vx;
     py = py + vy;
     Figura *butterfly = &Scena[FARFALLA];
     Figura* heart = &Scena[CUORE];
    // Renderizza ogni Figura nel vettore
    for (int i = 0; i < Scena.size(); ++i) {
        if (i == FARFALLA) {
            butterfly->Model = mat4(1.0);
            butterfly->Model = translate(butterfly->Model, vec3((float)(width) / 2.0 + px, (float)(height) / 2.0 + py, 0.0));
            butterfly->Model = scale(butterfly->Model, vec3(200.0, 200.0, 1.0));
        } else if (i == CUORE) {
            heart->Model = mat4(1.0);
            heart->Model = translate(heart->Model, vec3(mousex, mousey, 0));
            heart->Model = scale(heart->Model, vec3(150.0, 150.0, 1.0))
;
        }
        glUniformMatrix4fv(IdProj, 1, GL_FALSE, value_ptr(Projection));
        glUniformMatrix4fv(IdModel, 1, GL_FALSE, value_ptr(Scena[i].Model));
        glBindVertexArray(Scena[i].VAO);
        //Chiama glDrawArrays con la modalità specifica(Scena[i].render), a partire dal primo vertice, 
        glDrawArrays(Scena[i].render, 0, Scena[i].nv);
    }

}

void renderizza1(float currentTime) {


    glClearColor(clear_color.x, clear_color.y, clear_color.z, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT); // Pulisce il buffer colore

    my_interface(); // Disegna l’interfaccia ImGui

    /* Renderizza la GUI ImGui */
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());


    if (flag_wireframe)
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    else
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    Figura* heart = &Scena[CUORE];
    
    heart->Model = mat4(1.0);
    heart->Model = translate(heart->Model, vec3(mousex, mousey, 0));
    heart->Model = scale(heart->Model, vec3(100.0 * sin(currentTime * 2.0f * PI) + 450, 100.0 * sin(currentTime * 2.0f * PI) + 450, 1.0));

    glUniformMatrix4fv(IdProj, 1, GL_FALSE, value_ptr(Projection));
    glUniformMatrix4fv(IdModel, 1, GL_FALSE, value_ptr(heart->Model));
    glBindVertexArray(heart->VAO);
    //Chiama glDrawArrays con la modalità specifica(Scena[i].render), a partire dal primo vertice, 
    glDrawArrays(heart->render, 0, heart->nv);
}

void renderizza2(float currentTime) {


    glClearColor(clear_color.x, clear_color.y, clear_color.z, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT); // Pulisce il buffer colore

    my_interface(); // Disegna l’interfaccia ImGui

    /* Renderizza la GUI ImGui */
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());


    if (flag_wireframe)
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    else
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    float stepr = width / (float)numCols;
    float stepc = (height / 2) / (float)numRows;

    Figura* butterfly = &Scena[FARFALLA];
    Figura* heart = &Scena[CUORE];

    float x, y;
    for (int i = 0; i < numRows; i++) { // per ogni riga cambia l'ordinata
        y = height - i * stepc + stepc / 2;
        for (int j = 0; j < numCols; j++) { // per ogni colonna cambia l'ascissa
            x = j * stepr + stepr / 2;
            if (i % 2 == 0) {
                butterfly->Model = mat4(1.0f);
                butterfly->Model = translate(butterfly->Model, vec3(x, y, 0.0));
                butterfly->Model = scale(butterfly->Model, vec3(5 * 30.0 / numRows, 5 * 30.0 / numCols, 1.0));

                glUniformMatrix4fv(IdProj, 1, GL_FALSE, value_ptr(Projection));
                glUniformMatrix4fv(IdModel, 1, GL_FALSE, value_ptr(butterfly->Model));
                glBindVertexArray(butterfly->VAO);
                //Chiama glDrawArrays con la modalità specifica(Scena[i].render), a partire dal primo vertice, 
                glDrawArrays(butterfly->render, 0, butterfly->nv);
            }
            else {
                heart->Model = mat4(1.0);
                heart->Model = translate(heart->Model, vec3(x, y, 0));
                heart->Model = scale(heart->Model, vec3(5 * (10.0 * sin(currentTime * 2.0f * PI) + 50) / numRows, 5 * (10.0 * sin(currentTime * 2.0f * PI) + 50) / numRows, 1.0));

                glUniformMatrix4fv(IdProj, 1, GL_FALSE, value_ptr(Projection));
                glUniformMatrix4fv(IdModel, 1, GL_FALSE, value_ptr(heart->Model));
                glBindVertexArray(heart->VAO);
                //Chiama glDrawArrays con la modalità specifica(Scena[i].render), a partire dal primo vertice, 
                glDrawArrays(heart->render, 0, heart->nv);
            }
        }
    }
}

void renderizza3(float currentTime) {


    glClearColor(clear_color.x, clear_color.y, clear_color.z, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT); // Pulisce il buffer colore

    my_interface(); // Disegna l’interfaccia ImGui

    /* Renderizza la GUI ImGui */
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());


    if (flag_wireframe)
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    else
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    float stepr = width / (float)numCols;
    float stepc = (height / 2) / (float)numRows;
    float descentSpeed = 100.0;
    float amplitude = stepr / 2.0;
    float speed = 2.0;

    Figura* butterfly = &Scena[FARFALLA];
    Figura* heart = &Scena[CUORE];

    float x, y;
    for (int i = 0; i < numRows; i++) { // per ogni riga cambia l'ordinata
        float y_base = height - fmod(i * stepc + stepc / 2, height / 2);
        float offset = descentSpeed * currentTime + i * stepc;
        for (int j = 0; j < numCols; j++) { // per ogni colonna cambia l'ascissa
            float x_base = j * stepr + stepr / 2;
            x = x_base + amplitude * sin(speed * currentTime + i);
            y = y_base - offset;
            if (i % 2 == 0) {
                butterfly->Model = mat4(1.0f);
                butterfly->Model = translate(butterfly->Model, vec3(x, y, 0.0));
                butterfly->Model = scale(butterfly->Model, vec3(5 * 30.0 / numRows, 5 * 30.0 / numCols, 1.0));

                glUniformMatrix4fv(IdProj, 1, GL_FALSE, value_ptr(Projection));
                glUniformMatrix4fv(IdModel, 1, GL_FALSE, value_ptr(butterfly->Model));
                glBindVertexArray(butterfly->VAO);
                //Chiama glDrawArrays con la modalità specifica(Scena[i].render), a partire dal primo vertice, 
                glDrawArrays(butterfly->render, 0, butterfly->nv);
            }
            else {
                heart->Model = mat4(1.0);
                heart->Model = translate(heart->Model, vec3(x_base, y, 0));
                heart->Model = scale(heart->Model, vec3(5 * (10.0 * sin(currentTime * 2.0f * PI) + 50) / numRows, 5 * (10.0 * sin(currentTime * 2.0f * PI) + 50) / numRows, 1.0));

                glUniformMatrix4fv(IdProj, 1, GL_FALSE, value_ptr(Projection));
                glUniformMatrix4fv(IdModel, 1, GL_FALSE, value_ptr(heart->Model));
                glBindVertexArray(heart->VAO);
                //Chiama glDrawArrays con la modalità specifica(Scena[i].render), a partire dal primo vertice, 
                glDrawArrays(heart->render, 0, heart->nv);
            }
        }
    }
}