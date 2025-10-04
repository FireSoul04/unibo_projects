#include<GLFW/glfw3.h>
#include <iostream>

//extern serve per dichiarare una variabile senza allocarne memoria, indicando che la definizione avviene in un altro file, 
// consentendo così la condivisione di dati globali tra file sorgente diversi in un progetto C


double mousex, mousey;
double xpos, ypos;


void cursor_position_callback(GLFWwindow* window, double mouse_x, double mouse_y) {

    // Visualizza le coordinate del mouse che si muove sulla finestra grafica
    mousex = mouse_x;
    mousey = mouse_y;
    }


void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
    {
        //glfwGetCursorPos è un'utilità fornita dalla libreria GLFW che permette di recuperare la posizione attuale del cursore
        //del mouse all'interno di una finestra OpenGL.
        glfwGetCursorPos(window, &xpos, &ypos);
    }
}






void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
     
    // Esegui le azioni desiderate in base alla quantità di scorrimento
    std::cout << "Scorrimento x: " << xoffset << " y: " << yoffset << std::endl;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {

    // Se il tasto ESCAPE è premuto, chiude la finestra
    switch (key) {
    case GLFW_KEY_ESCAPE:
        if (action == GLFW_PRESS)
            //Imposta a True il flag booleano di chiusura della finestra
            glfwSetWindowShouldClose(window, GLFW_TRUE);
        break;

    
    default:
        // codice da eseguire se expression non corrisponde a nessun valore
        break;
    }

}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    
    // Esegui le azioni desiderate in base alle nuove dimensioni
    std::cout << "Dimensione finestra larghezza: " << width << " altezza " << height << std::endl;
}