#include "lib.h"
#include "ShaderMaker.h"
#include "strutture.h" 
#include "inizializzazioni.h"
#include "init_geometrie.h"
#include "earcut.hpp"
#include "gestione_interazioni.h"
#include "Init_Finestra_Eventi.h"
#include <array>
#include "init_GLFW_OpenGL.h"
#include <ImGui\imgui.h>           // Libreria core ImGui
#include <ImGui\imgui_impl_glfw.h> // Integrazione ImGui con GLFW (gestione finestra/input)
#include <ImGui\imgui_impl_opengl3.h> // Integrazione ImGui con OpenGL3 (rendering)
#include "Scena.h"
#include "rendering.h"
#include "Gui.h"
#define PI 3.14159265358979323
//Variabili globali -------------------------------------------------------------------
unsigned int programId, programId_CP, programId_Triangul, programId_TG;  //Identificativo dello shader program
unsigned int IdProj_Triangul, IdModel_Triangul;
int height, width; //altezza e larghezza della finestra
GLFWwindow* window;
vector<Figura> Scena;
Figura assi;
Curva curva;

ImVec4 clear_color = ImVec4(0.45f, 0.0f, 0.0f, 1.00f);
mat4 Projection;
GLuint IdProj, IdModel,IdCurve,IdColorA,IdColorB, IdProj_TG, IdModel_TG;
int selected_point = -1;
 

//----------------------------------------------------------------------------------------
int renderFunctionSelector = 0; // 0=renderizza1, 1=renderizza2, ecc.
 


int main(void)
{ 
    //Inizializza GLFW, imposta le proprietà del contesto e del profile
    int flag_gl_GLFW= init_gl_GLFW();

    /* Inizializza la finestra opengl ed associa contesto e la gestione degli eventi */
    int flag= inizializza_window_context_events();
    //Inizializza l'intefaccia ImGUI
    Initialize_IMGUI(window);
    
    //Inizializza gli shader 
    INIT_SHADER();
    //Costruisce la scena
    costruisci_Scena(&Scena);

    //Gestione della trasparenza:
    /*
    In OpenGL, la funzione glBlend serve a definire come combinare i colori di un pixel sorgente (che stiamo disegnabdo) e di un pixel destinazione (già presente nel framebuffer)
     quando si disegnano oggetti trasparenti.
    In questo caso specifico, glBlend(GL_SRC_ALPHA, GL_ONES_MINUS_SRC_ALPHA); indica che :
     GL_SRC_ALPHA: Il valore alfa del pixel sorgente(quello che stiamo disegnando) verrà utilizzato come fattore di miscelazione per il colore sorgente.
     GL_ONES_MINUS_SRC_ALPHA : Il valore alfa del pixel destinazione(quello già presente nel buffer) verrà sottratto da 1 e poi utilizzato come fattore di miscelazione
     per il colore destinazione. (già presente nel framebuffer
*/
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
   
    //Le coordinate di input sono in un sistema mondo(o spazio vista) 
    // definito da(0, 0) in basso a sinistra e (width, height) in alto a destra.
    // La matrice ortografica trasla e scala queste coordinate per far sì che il mondo 2d 
    // venga normalizzato nel quadrato standard NDC, che va da - 1 a + 1 in X e Y.

    Projection = ortho(-1.0,1.0,-1.0,1.0);
    IdProj = glGetUniformLocation(programId, "Projection");
    IdModel = glGetUniformLocation(programId, "Model");
    IdColorA= glGetUniformLocation(programId_Triangul, "colorA");
    IdColorB= glGetUniformLocation(programId_Triangul, "colorB");
    IdModel_Triangul = glGetUniformLocation(programId_Triangul, "Model");
    IdProj_Triangul = glGetUniformLocation(programId_Triangul, "Projection");
    IdModel_TG = glGetUniformLocation(programId_TG, "Model");
    IdProj_TG = glGetUniformLocation(programId_TG, "Projection");
    IdCurve = glGetUniformLocation(programId, "useCurve");

    /* Loop until the user closes the window */
    INIT_ASSI(&assi);
    INIT_VAO(&assi);
    //Ver poter fare l'uodate del VAO bisogna inizializzare lo spazio ad un numero massimo che si è sicuri di non superare
    curva.ncp = 100;
    curva.nv = 200;
    curva.ntg = 100;
    INIT_VAO_DYNAMIC(&curva,true);

    while (!glfwWindowShouldClose(window))
    {
        
        float currentTime = glfwGetTime(); //rappresenta i secondi trascorsi dall’avvio di GLFW e cresce continuamente.

        //Utilizzare renderizza1(currentTime) per la soluzione del punto 1 dell'esercitazione;
        //  renderizza2(currentTime) per la soluzione del punto 2 dell'esercitazione, etc
        renderizza(currentTime);

        
        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }
    /* Pulizia finale */

    close_GUI();               // Libera risorse ImGui
    glfwDestroyWindow(window); // Distrugge la finestra
    glDeleteProgram(programId);

    glfwTerminate();
    return 0;
}


  