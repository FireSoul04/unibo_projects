#pragma once
#include <glad/glad.h>
#include "ShaderMaker.h"
#include "strutture.h"
#include "init_geometrie.h"
#include "inizializzazioni.h"
#include "gestione_curve.h"
#include "earcut.hpp"
#include "Gui.h"
#include <array>
#include <ImGui\imgui.h>           // Libreria core ImGui
#include <ImGui\imgui_impl_glfw.h> // Integrazione ImGui con GLFW (gestione finestra/input)
#include <ImGui\imgui_impl_opengl3.h> // Integrazione ImGui con OpenGL3 (rendering)
#include "lib.h"
#define PI 3.14159265358979323
extern int  width, height;
extern vector<Figura>Scena; 
extern ImVec4 clear_color;
bool showMenu = false, visualizza_PC = true;;
double mousex, mousey; //Coordinate del mouse
bool flag_wireframe;

// Identificatori delle variabili uniformi:  Model  e Projection
extern GLuint IdProj, IdModel, IdCurve, IdColorA,IdColorB, IdProj_TG, IdModel_TG;
extern GLuint IdProj_Triangul, IdModel_Triangul;
extern unsigned int programId, programId_CP, programId_Triangul, programId_TG;
extern Figura assi;
extern Curva curva;
bool visualizzaTg, modTg, riempi, tangenteModificata;
//Inizializzazione parametrizzazione e Modalità dle mouse.
int param=0, Mod=0;
extern mat4 Projection; // matrice di proiezione: dalle coordinate del mondo alle coordinate di display normalizzate
float* t;


 
void renderizza(float currentTime){

    using Coord = float;
    using Point2D = std::array<Coord, 2>;

    int i;
    float step_t;


    glClearColor(clear_color.x, clear_color.y, clear_color.z, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT); // Pulisce il buffer colore

    
 
        
     if (flag_wireframe)
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    else
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

     glLineWidth(4.0);
     glPointSize(10.0);
 
     //Disegno gli assi
     glUseProgram(programId);
     glUniformMatrix4fv(IdProj, 1, GL_FALSE, value_ptr(Projection));
     glUniformMatrix4fv(IdModel, 1, GL_FALSE, value_ptr(assi.Model));
     glBindVertexArray(assi.VAO);
     //Chiama glDrawArrays con la modalità specifica(Scena[i].render), a partire dal primo vertice, 
      glDrawArrays(assi.render, 0, assi.nv);
      
      //Visualizza vertici di controllo e poligono di controllo
      if (visualizza_PC) {

        glUseProgram(programId_CP);
        //Attiva il VBO_vertices dela curva
        UPDATE_VAO_DYNAMIC(&curva, true);
        glUniformMatrix4fv(IdProj, 1, GL_FALSE, value_ptr(Projection));
        glUniformMatrix4fv(IdModel, 1, GL_FALSE, value_ptr(assi.Model));
        glBindVertexArray(curva.VAO);
        glDrawArrays(GL_LINE_STRIP, 0, curva.CP.size());  //Disegna i vertici di controllo della curva come punti isolati
        glDrawArrays(GL_POINTS, 0, curva.CP.size());
        //Visualizzazione dei vertici come punti
     }
        
      if (curva.CP.size() > 2) {
          if (param == 0) {
              t_equidistanti();
          } else {
              t_corde();
          }
		  glUseProgram(programId);
		  curva.Model = mat4(1.0f);
		  CostruisciHermite(&curva);

		  glBindVertexArray(curva.VAO);
          glDrawArrays(GL_LINE_STRIP, 0, curva.vertices.size());
      }

            //Triangolazione della curva e rendering della curva triangolarizzata
            if (riempi) {
                vector<Point2D> polygon2D;

                polygon2D.reserve(curva.vertices.size());
                for (const auto& v : curva.vertices) {
                    polygon2D.push_back(Point2D{ v.x, v.y });
                }
                               
                vector<vector<Point2D>> polygon = { polygon2D };
                // Triangolazione facebndo uso della funzione eartcut
                vector<uint32_t> indices = mapbox::earcut<uint32_t>(polygon);
                // Output degli indici dei triangoli
                curva.indices = indices;
                UPDATE_VAO_DYNAMIC(&curva);
                vec4 colorA = vec4(1.0, 0.0, 0.0, 1.0);
                vec4 colorB = vec4(1.0, 0.5, 1.0, 1.0);
                glUseProgram(programId_Triangul);
                glUniform4f(IdColorA, colorA.r, colorA.g, colorA.b, colorA.a);
                glUniform4f(IdColorB, colorB.r, colorB.g, colorB.b, colorB.a);
                glUniformMatrix4fv(IdProj_Triangul, 1, GL_FALSE, value_ptr(Projection));
                glUniformMatrix4fv(IdModel_Triangul, 1, GL_FALSE, value_ptr(curva.Model));
                glBindVertexArray(curva.VAO);
                glDrawElements(GL_TRIANGLES, curva.indices.size(), GL_UNSIGNED_INT, 0);  //Modalità di rendering GL_LINE_STRIP: tutti i vertici vengono uniti da una spezzata
                glBindVertexArray(0);

            }
            
     

     if (showMenu){
            my_interface(); // Disegna l’interfaccia ImGui
            /* Renderizza la GUI ImGui */
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
      }

}

 