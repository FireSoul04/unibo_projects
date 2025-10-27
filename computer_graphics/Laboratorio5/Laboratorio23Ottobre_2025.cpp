#include "lib.h"
#include "ShaderMaker.h"
#include "strutture.h" 
#include "inizializzazioni.h"
#include "init_geometrie.h"
#include "gestione_interazioni.h"
#include "Init_Finestra_Eventi.h"
#include "init_GLFW_OpenGL.h"
#include <ImGui\imgui.h>           // Libreria core ImGui
#include <ImGui\imgui_impl_glfw.h> // Integrazione ImGui con GLFW (gestione finestra/input)
#include <ImGui\imgui_impl_opengl3.h> // Integrazione ImGui con OpenGL3 (rendering)
#include "Scena.h"
#include "rendering.h"
#include "Gui.h"
#define PI 3.14159265358979323
//Variabili globali -------------------------------------------------------------------
unsigned int programId, programId_BK, programId_BK1, programId_BK2, programId_BK3, programId_BK4, programId_BK5, programId_BK6, programId_BK7, programId_BK8;  //Identificativo dello shader program

int height, width; //altezza e larghezza della finestra
GLFWwindow* window;
vector<Figura> Scena;
Figura astronave, proiettile, proiettili;
 
ImVec4 clear_color = ImVec4(0.45f, 0.0f, 0.0f, 1.00f);
mat4 Projection, Projection_Background;
GLuint IdProj, IdModel;
GLuint IdProj_BK, IdModel_BK,id_res_BK,id_time_BK;
 
unsigned int  selected_bk;

float deltaTime = 0.0f;
float lastFrame;

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
    selected_bk = programId;
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

    Projection = ortho(0.0f, float(width), 0.0f, float(height));

     
    // Ottiene la posizione della variabile uniforme "Projection" nel programma shader principale
    IdProj = glGetUniformLocation(programId, "Projection");

    // Ottiene la posizione della variabile uniforme "Model" nel programma shader principale
    IdModel = glGetUniformLocation(programId, "Model");


    // Ottiene la posizione della variabile uniforme "Projection" nel programma shader del background
    IdProj_BK = glGetUniformLocation(selected_bk, "Projection");

    // Ottiene la posizione della variabile uniforme "Model" nel programma shader del background
    IdModel_BK = glGetUniformLocation(selected_bk, "Model");

    // Ottiene la posizione della variabile uniforme "iResolution" (risoluzione viewport) nel programma shader del background
    //id_res_BK = glGetUniformLocation(selected_bk, "iResolution");

    // Ottiene la posizione della variabile uniforme "iResolution" (risoluzione viewport) nel programma shader del background
    //id_time_BK = glGetUniformLocation(selected_bk, "iTime");
    /* Loop until the user closes the window */
   
    while (!glfwWindowShouldClose(window))
    {

         
        float currentTime = glfwGetTime(); //rappresenta i secondi trascorsi dall’avvio di GLFW e cresce continuamente.
        deltaTime = currentTime - lastFrame;
        lastFrame = currentTime;
        //Utilizzare renderizza1(currentTime) per la soluzione del punto 1 dell'esercitazione;
        //  renderizza2(currentTime) per la soluzione del punto 2 dell'esercitazione, etc
        renderizza(currentTime);
        //ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }
    /* Pulizia finale */

    close_GUI();               // Libera risorse ImGui
    glfwDestroyWindow(window); // Distrugge la finestra
    glDeleteProgram(programId);
    for (int i = 0; i < Scena.size(); i++)
    {
        glDeleteBuffers(1, &Scena[i].VBO_vertices);
        glDeleteBuffers(1, &Scena[i].VBO_colors);
        glDeleteVertexArrays(1, &Scena[i].VAO);
    }
    glfwTerminate();
    return 0;
}


  