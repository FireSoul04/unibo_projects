#pragma once
#include "lib.h"
#include "Gui.h"
#include "strutture.h"
#include "inizializzazioni.h"
#include "init_geometrie.h"
#include <ImGui\imgui.h>           // Libreria core ImGui
#include <ImGui\imgui_impl_glfw.h> // Integrazione ImGui con GLFW (gestione finestra/input)
#include <ImGui\imgui_impl_opengl3.h> // 

extern GLFWwindow* window;
extern bool isMouseDown;
extern float r, g, b;
extern double mousex,mousey;
extern int height, width;
extern float dx, dy,angolo;
extern bool showMenu; // Stato del menu
extern float  w_update, h_update;
extern mat4 Projection,Projection_Background;
extern Figura proiettile,astronave;
extern unsigned int programId;
extern vector<Figura> proiettili;
extern float x_offset, y_offset;
extern   float w_update, h_update;
void cursor_position_callback(GLFWwindow* window, double xpos, double ypos) {

    // Visualizza le coordinate del mouse che si muove sulla finestra grafica

    mousex = xpos;
    mousey =  height-ypos;
    //std::cout << "Coordinate del mouse  : x = " << xpos << ", y = " << ypos << std::endl;
}


void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    //Se il bottone sinistro del mouse è premuto, visualizza le coordinate del mpuse nella posizione in cui il bottone centrale
  //  del mouse è premuto.
    double xpos, ypos;
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
    {
        //glfwGetCursorPos è un'utilità fornita dalla libreria GLFW che permette di recuperare la posizione attuale del cursore
        //del mouse all'interno di una finestra OpenGL.
        glfwGetCursorPos(window, &xpos, &ypos);
        mousex = xpos;
        mousey = height-ypos;
        //std::cout << "Coordinate del mouse tasto sinistro premuto : x = " << xpos << ", y = " << ypos << std::endl;
    }
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {

    // Se il tasto ESCAPE è premuto, chiude la finestra
    switch (key) {
    case GLFW_KEY_ESCAPE:
        if (action == GLFW_PRESS)
            //Imposta a True il flag booleano di chiusura della finestr
            glfwSetWindowShouldClose(window, GLFW_TRUE);
        break;
    case GLFW_KEY_W:
        dy = dy + 10.0;
        break;
    case GLFW_KEY_S:
        dy = dy - 10.0;
        break;

    case GLFW_KEY_A:
        dx = dx - 10.0;
        break;
    case GLFW_KEY_D:
        dx = dx + 10.0;
        break;

    case GLFW_KEY_R:
        angolo=angolo+10.0;
        break;
    case GLFW_KEY_F1:
        if (action == GLFW_PRESS)
        {
            if (key == GLFW_KEY_F1 && action == GLFW_PRESS)
                showMenu = !showMenu;
        }
        break;
        
    case GLFW_KEY_SPACE:
        if (action == GLFW_PRESS) {
            Figura nuovoProiettile;
            nuovoProiettile.isalive = true;
			nuovoProiettile.position = vec3(0.0f);
            nuovoProiettile.nTriangles = 60;
            nuovoProiettile.shader_programId = programId;
			nuovoProiettile.scale = vec3(10.0f, 10.0f, 1.0f);
           // Ad ogni pressione si genera un nuovo proiettile e si fa il pushback nel vector proiettili  
			INIT_CIRCLE(0.0f, 0.0f, 1.0f, 1.0f, &nuovoProiettile, vec4(0.5f, 0.5f, 0.5f, 1.0f), vec4(0.3f, 0.3f, 0.3f, 1.0f));
            
            nuovoProiettile.Model = scale(astronave.Model, vec3(0.1f, 0.1f, 1.0f));

			INIT_VAO(&nuovoProiettile);
			proiettili.push_back(nuovoProiettile);
        }
    }

}


    
     

// ------------------------------------------------------------------

void framebuffer_size_callback0(GLFWwindow* window, int w, int h)
{
   
}

void framebuffer_size_callback(GLFWwindow* window, int w, int h)
{
    // Evitare divisioni per zero
    if (h == 0) h = 1;

    Projection = ortho(0.0f, (float)width, 0.0f, (float)height);


    // Imposta il viewport con gli offset per centrarlo
    glViewport(0.0, 0.0, w, h);
}


// Funzione di callback chiamata ogni volta che la finestra (framebuffer) viene ridimensionata.
// Gestisce il corretto rapporto di aspetto e centra la viewport rispetto alle dimensioni della finestra.
void framebuffer_size_callback1(GLFWwindow* window, int w, int h)
{
    float x_offset = 0.0, y_offset = 0.0; // Offset per centrare la viewport

    // Prevenzione di divisione per zero
    if (h == 0) h = 1;

    // Aggiorna la matrice di proiezione ortografica in base alle dimensioni del mondo virtuale
    Projection = ortho(0.0f, (float)width, 0.0f, (float)height);

    // Calcola il rapporto di aspetto del “mondo”  
    float AspectRatio_mondo = (float)width / (float)height;

    // Adatta la viewport a seconda del rapporto tra il mondo e la finestra
    if (AspectRatio_mondo > (float)w / (float)h)
    {
        // Il mondo è relativamente più largo della finestra.
        // La larghezza della viewport è quella della finestra, l’altezza viene ridotta.
        w_update = (float)w;
        h_update = w / AspectRatio_mondo;
        // Calcola l’offset verticale per centrare la viewport nel framebuffer più alto
        y_offset = ((float)h - h_update) / 2.0f;
    }
    else
    {
        // Il mondo è relativamente più stretto o alto della finestra.
        // L’altezza della viewport è quella della finestra, la larghezza viene ridotta.
        h_update = (float)h;
        w_update = h * AspectRatio_mondo;
        // Calcola l’offset orizzontale per centrare la viewport nel framebuffer più largo
        x_offset = ((float)w - w_update) / 2.0f;
    }

    // Imposta la viewport OpenGL con offset e dimensioni calcolate per centrarla e mantenere il giusto aspect ratio
    glViewport(x_offset, y_offset, w_update, h_update);
}
