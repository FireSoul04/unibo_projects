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
unsigned int programId;  //Identificativo dello shader program

int height=1200, width=1800; //altezza e larghezza della finestra
GLFWwindow* window;
vector<Figura> Scena;

 
ImVec4 clear_color = ImVec4(0.45f, 0.0f, 0.0f, 1.00f);
mat4 Projection;
GLuint IdProj, IdModel;

//----------------------------------------------------------------------------------------


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

    Projection = ortho(0.0f, float(width), 0.0f, float(height));
    IdProj = glGetUniformLocation(programId, "Projection");
    IdModel = glGetUniformLocation(programId, "Model");

    /* Loop until the user closes the window */

    while (!glfwWindowShouldClose(window))
    {
        
        float currentTime = glfwGetTime(); //rappresenta i secondi trascorsi dall’avvio di GLFW e cresce continuamente.


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
    for (int i = 0; i < Scena.size(); i++)
    {
        glDeleteBuffers(1, &Scena[i].VBO_vertices);
        glDeleteBuffers(1, &Scena[i].VBO_colors);
        glDeleteVertexArrays(1, &Scena[i].VAO);
    }
    glfwTerminate();
    return 0;
}


  