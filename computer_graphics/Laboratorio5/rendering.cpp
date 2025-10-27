#pragma once
#include <glad/glad.h>
#include "ShaderMaker.h"
#include "strutture.h"
#include "init_geometrie.h"
#include "inizializzazioni.h"
#include "Utilities.h"
#include "Gui.h"
#include <ImGui\imgui.h>           // Libreria core ImGui
#include <ImGui\imgui_impl_glfw.h> // Integrazione ImGui con GLFW (gestione finestra/input)
#include <ImGui\imgui_impl_opengl3.h> // Integrazione ImGui con OpenGL3 (rendering)
#include "lib.h"
#define PI 3.14159265358979323
extern int  width, height;

extern vector<Figura>Scena; 
extern Figura astronave, proiettile;
extern ImVec4 clear_color;
 
double mousex, mousey; //Coordinate del mouse
float dx = 0.0,  dy=0.0;
float alpha;
bool flag_wireframe;
bool show_bounding_boxes = false;
int numRows = 6;
int numCols = 6;
// Identificatori delle variabili uniformi:  Model  e Projection
extern GLuint IdProj, IdModel,IdProj_BK, IdModel_BK, id_res_BK,id_time_BK;
extern unsigned int programId;
bool showMenu = false;
extern mat4 Projection; // matrice di proiezione: dalle coordinate del mondo alle coordinate di display normalizzate
extern unsigned int selected_bk;
float angolo = 0.0;
float w_update, h_update;
extern float deltaTime;
extern vector<Figura> proiettili;

 // Funzione per disegnare una forma grafica con la possibilità di visualizzare la bounding box (BB)
// Parametri:
// - forma: riferimento a un oggetto Figura che contiene dati della forma da disegnare
// - wireframe: opzione booleana per disegnare la forma in modalità wireframe (solo i contorni) oppure riempita (default: false)
// - showBB: opzione booleana per visualizzare la bounding box della forma come un poligono a 4 lati (default: false)

 void disegnaFormaConBB(Figura& forma, bool wireframe = false, bool showBB = false) {
    // Se wireframe è true, imposta la modalità di disegno in modo che tutte le facce siano solo contorni
    if (wireframe)
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    else
        // Altrimenti, riempi le facce in modalità solida
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    // Associa il Vertex Array Object (VAO) della forma, che contiene i dati dei vertici da disegnare
    glBindVertexArray(forma.VAO);

    // Disegna i vertici della forma come specificato da forma.render,
    // a partire dal primo vertice (0), per (forma.nv - 4) vertici in totale
    // La sottrazione di 4 è per escludere i vertici della bounding box
     glDrawArrays(forma.render, 0, forma.nv - 4);
    if (showBB)
        // Se showBB è true, disegna la bounding box con una line loop collegando gli ultimi 4 vertici
        glDrawArrays(GL_LINE_LOOP, forma.nv - 4, 4);
}



void PosizionaOrientaScala(Figura* forma, float angoloLocal = -1.0f, bool restituisciSenzaScala = false, glm::mat4* outModelNoScale = nullptr)
{
    /*

Figura* forma — puntatore all'oggetto su cui si applicano le trasformazioni e dove si salva la matrice Model.

float angoloLocal = -1.0f — parametro opzionale per specificare l'angolo di rotazione in gradi. Se non passato o negativo, si usa la variabile globale angolo.

bool restituisciSenzaScala = false — flag che indica se restituire anche la matrice senza scala.

glm::mat4* outModelNoScale = nullptr — puntatore opzionale a una matrice su cui scrivere la trasformazione senza scala.*/

    forma->rotation = (angoloLocal < 0.0f) ? angolo : angoloLocal;
    // Calcolo matrice con scala
    forma->Model = glm::mat4(1.0f);
    forma->Model = glm::translate(forma->Model, glm::vec3(forma->position.x + dx, forma->position.y + dy, 0.0f));
    forma->Model = glm::rotate(forma->Model, glm::radians(forma->rotation), glm::vec3(0, 0, 1));
    forma->Model = glm::scale(forma->Model, forma->scale);

    // Se richiesto, restituisce matrice senza scala tramite puntatore
    if (restituisciSenzaScala && outModelNoScale != nullptr) {
        glm::mat4 modelNoScale = glm::mat4(1.0f);
        modelNoScale = glm::translate(modelNoScale, glm::vec3(forma->position.x + dx, forma->position.y + dy, 0.0f));
        modelNoScale = glm::rotate(modelNoScale, glm::radians(forma->rotation), glm::vec3(0, 0, 1));
        // nessuna scala qui
        *outModelNoScale = modelNoScale;
    }
}

void renderizza(float currentTime) {
    mat4 Model_astro;
    glClearColor(clear_color.x, clear_color.y, clear_color.z, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // Render background
    Scena[BACKGROUND].shader_programId = selected_bk;
    
    usaShaderConUniforms(Scena[BACKGROUND].shader_programId, Projection, Scena[BACKGROUND].Model, currentTime, glm::vec2((float)width, height));
    
    disegnaFormaConBB(Scena[BACKGROUND], flag_wireframe, show_bounding_boxes);

    // Aggiorna matrice modello astronave e memorizza in Model_astro, la mastrice senza scala
    PosizionaOrientaScala(&astronave, -1.0,true, &Model_astro);
   //aggiorna BB dell'astronave
  
    // Disegna astronave
    usaShaderConUniforms(astronave.shader_programId, Projection, astronave.Model, currentTime, glm::vec2((float)width, height));
    disegnaFormaConBB(astronave, flag_wireframe, show_bounding_boxes);
    

    //To do
    // Aggiornare i proiettili (la loro posizione di partenza coincide con quella dell'astronave)
    aggiornaProiettili(deltaTime);

    //To do
    // Disegnare tutti i proiettili vivi
    for (auto& p : proiettili) {
        if (p.isalive) {
            usaShaderConUniforms(p.shader_programId, Projection, p.Model, currentTime, vec2((float)width, (float)height));
			disegnaFormaConBB(p, flag_wireframe, show_bounding_boxes);
        }
    }
   
    // Disegna altre forme (farfalla ecc)
    constexpr Forma forme[] = { FARFALLA,CUORE };
    for (auto& d : forme) {
        //To do  Gestione collisioni
        for (auto& p : proiettili) {
            if (checkCollision(p, Scena[d])) {
				Scena[d].isalive = false;
				p.isalive = false;
                break;
            }
        }

        if (Scena[d].isalive)
        {
            PosizionaOrientaScala(&Scena[d],0.0);
            //Aggiorna BB di Scena[d];
            updateBB(&Scena[d]);
            usaShaderConUniforms(Scena[d].shader_programId, Projection, Scena[d].Model, currentTime, glm::vec2((float)width, height));
            disegnaFormaConBB(Scena[d], flag_wireframe, show_bounding_boxes);
        }
    }

    if (showMenu) {
        my_interface();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }
} 