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

Figura heart;
double mousex, mousey; //Coordinate del mouse
float alpha;
bool flag_wireframe;

void renderizza(float currentTime){

      
    glClearColor(clear_color.x, clear_color.y, clear_color.z, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT); // Pulisce il buffer colore

    my_interface(); // Disegna l’interfaccia ImGui

    /* Renderizza la GUI ImGui */
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    // Muovi il cuore in base alla posizione del mouse
    float hx = 2 * mousex / width - 1.0f;
    float hy = 2 * mousey / height - 1.0f;
    //INIT_HEART(hx, hy, 0.02, 0.02, &heart, vec4{1.0, 1.0, 1.0, 1.0}, vec4{0.0, 1.0, 1.0, 1.0});

    // Cambia dimensione in base alla posizione del mouse
    float raggiox = (sin(currentTime * 2.0 * PI) * 0.25 + 0.75) * 0.02;
    INIT_HEART(hx, hy, raggiox, raggiox, &heart, vec4{1.0, 1.0, 1.0, 1.0}, vec4{0.0, 1.0, 1.0, 1.0});

    glBindBuffer(GL_ARRAY_BUFFER, Scena[CUORE].VBO_vertices);
    glBufferSubData(GL_ARRAY_BUFFER, 0, heart.vertices.size() * sizeof(vec3), heart.vertices.data());

    heart.vertices.clear();
    heart.colors.clear();

    if (flag_wireframe) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    } else {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }

    // Renderizza ogni Figura nel vettore
    for (int i = 0; i < Scena.size(); ++i) {
        glBindVertexArray(Scena[i].VAO);
        //Ciama glDrawArrays con la modalità specifica(Scena[i].render), a partire dal primo vertice, 
        glDrawArrays(Scena[i].render, 0, Scena[i].nv);
    }
 
}
