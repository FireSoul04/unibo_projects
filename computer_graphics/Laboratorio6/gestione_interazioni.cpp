#pragma once
#include "lib.h"
#include "strutture.h"
#include "inizializzazioni.h"
#include "gestione_curve.h"
#include <ImGui\imgui.h>           // Libreria core ImGui
#include <ImGui\imgui_impl_glfw.h> // Integrazione ImGui con GLFW (gestione finestra/input)
#include <ImGui\imgui_impl_opengl3.h> // Integrazione ImGui con OpenGL3 (rendering)
extern GLFWwindow* window;
extern bool isMouseDown;
extern float r, g, b;
extern double mousex,mousey;
extern int height, width;
extern float* t;
extern bool showMenu;
extern Curva curva;
extern int Mod;
extern bool modTg;
extern int selected_point;
 
void cursor_position_callback(GLFWwindow* window, double xpos, double ypos) {
    float mousex_m, mousey_m;

    mousex = xpos;
    mousey = height - ypos;

    mousex_m = 2 * (mousex / width) - 1;
    mousey_m = 2 * (mousey / height) - 1;


 
    if (Mod == 1  && !modTg)
    {

        if (selected_point >= 0)
        {
            curva.CP[selected_point] = vec3(mousex_m, mousey_m, 0.0);
            curva.colCP[selected_point] = vec4(1.0, 0.0, 0.0, 1.0);
           
        }
    }


}

 


void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    //Se il bottone sinistro del mouse è premuto, visualizza le coordinate del mpuse nella posizione in cui il bottone centrale
  //  del mouse è premuto.
    double xpos, ypos, mousex_m, mousey_m, dist, dist1, TOLL = 0.1;
    if (button == GLFW_MOUSE_BUTTON_LEFT && !ImGui::IsAnyItemHovered())
    {

        if (action == GLFW_PRESS)
        {

            //glfwGetCursorPos è un'utilità fornita dalla libreria GLFW che permette di recuperare la posizione attuale del cursore
            //del mouse all'interno di una finestra OpenGL.
            if (Mod == 0) {
                glfwGetCursorPos(window, &xpos, &ypos);
                mousex = xpos;
                mousey = height - ypos;

                mousex_m = 2.0 / (float)(width)*mousex - 1;
                mousey_m = 2.0 / (float)(height)*mousey - 1;

                curva.CP.push_back(vec3(mousex_m, mousey_m, 0.0));
                curva.colCP.push_back(vec4(0.0, 1.0, 1.0, 1.0));
                //Inizializzo a zero i valori di Ten, Bias e Cont del CP inserito
                curva.Tens.push_back(0.0);
                curva.Bias.push_back(0.0);
                curva.Cont.push_back(0.0);
                curva.Derivata.push_back(vec3(0.0, 0.0, 0.0));
                curva.ncp = curva.CP.size();
                
                //UPDATE_VAO_DYNAMIC(&curva, true);
            }
            if (Mod == 1)
            {
                glfwGetCursorPos(window, &xpos, &ypos);
                mousex = xpos;
                mousey = height - ypos;
                mousex_m = 2.0 / (float)(width)*mousex - 1;  //MAppo le coordiante del mouse nella finestra sul mondo che nel nostro caso è [-1,1]x[-1,1]
                mousey_m = 2.0 / (float)(height)*mousey - 1;
                vec2 mousepos = vec2(mousex_m, mousey_m);
                dist = 1000;
                
                 
                for (int i = 0; i < curva.ncp; ++i) {
                    
                    //calcolo la distanza tra la poszione in cui si trova il mouse e ciascuno dei vertici già disegnati sulla finestra 
                    vec2 vertice = vec2(curva.CP[i].x, curva.CP[i].y);
                    dist1 = glm::distance(mousepos, vertice);
                    
                    
                    if (dist1 < dist) {
                        selected_point = i;   //Il vertice con la distanza minima dal mouse viene considerato il punto selezionato.
                        dist = dist1;
                    }
                }
                cout << "Ho selezionato il punto "<<selected_point << endl;
                if (dist > TOLL)
                    selected_point = -1;
            }
            else if (Mod == 2)   //elimina l'ultimo vertice inserito
            {
                if (curva.CP.size() > 0) {
					//Elimino l'ultimo vertice di controllo introdotto.
					curva.CP.pop_back();
					curva.colCP.pop_back();
                }
            }

        }
    }
    if (button == GLFW_MOUSE_BUTTON_RIGHT)
        Mod = 0;  //Torno in modalità inserisce e confermo la posizone del vertice dopo lo spostamento
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {

    // Se il tasto ESCAPE è premuto, chiude la finestra
    switch (key) {
    case GLFW_KEY_ESCAPE:
        if (action == GLFW_PRESS)
            //Imposta a True il flag booleano di chiusura della finestr
            glfwSetWindowShouldClose(window, GLFW_TRUE);
        break;
    case GLFW_KEY_F1:
        if (action == GLFW_PRESS)
        {
            if (key == GLFW_KEY_F1 && action == GLFW_PRESS)
                showMenu = !showMenu;
        }
        break;
    case GLFW_KEY_T:
        if (mods & GLFW_MOD_SHIFT)
            curva.Tens[selected_point] = curva.Tens[selected_point] + 0.1;
        else
            curva.Tens[selected_point] = curva.Tens[selected_point] - 0.1;
        //Aggiorno la derivata nel punto selezionato utilizzando
        // Tens,Bias e Cont aggiornati per il vertice selezionato
        curva.Derivata.at(selected_point).x = dx(selected_point, t, &curva);
        curva.Derivata.at(selected_point).y = dy(selected_point, t, &curva);

        break;

    case GLFW_KEY_C:
        if (mods & GLFW_MOD_SHIFT)
            curva.Cont[selected_point] = curva.Cont[selected_point] + 0.1;
        else
            curva.Cont[selected_point] = curva.Cont[selected_point] - 0.1;
        //Aggiorno la derivata nel punto selezionato utilizzando
        // Tens,Bias e Cont aggiornati per il verice selezionato
        curva.Derivata.at(selected_point).x = dx(selected_point, t, &curva);
        curva.Derivata.at(selected_point).y = dy(selected_point, t, &curva);

        break;

    case GLFW_KEY_B:
        if (mods & GLFW_MOD_SHIFT)
            curva.Bias[selected_point] = curva.Bias[selected_point] + 0.1;
        else
            curva.Bias[selected_point] = curva.Bias[selected_point] - 0.1;

        //Aggiorno la derivata nel punto selezionato utilizzando
        // Tens,Bias e Cont aggiornati per il verice selezionato
        curva.Derivata.at(selected_point).x = dx(selected_point, t, &curva);
        curva.Derivata.at(selected_point).y = dy(selected_point, t, &curva);

        break;
   
    default:

        break;
    }

}

void framebuffer_size_callback(GLFWwindow* window, int w, int h)
{
    glViewport(0.0, 0.0, w, h);

    width = w;
    height = h;
   
}
