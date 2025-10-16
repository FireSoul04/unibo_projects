#pragma once
#include "lib.h"


extern GLFWwindow* window;
extern bool isMouseDown;
extern float r, g, b;
extern double mousex,mousey;
extern int height, width;
extern float vx, vy;
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
    float step = 1.0f;
    // Se il tasto ESCAPE è premuto, chiude la finestra
    switch (key) {
    case GLFW_KEY_ESCAPE:
        if (action == GLFW_PRESS)
            //Imposta a True il flag booleano di chiusura della finestr
            glfwSetWindowShouldClose(window, GLFW_TRUE);
        break;
    default:
        break;
    }

    vx = 0.0f;
    vy = 0.0f;
    if (key == GLFW_KEY_W) {
        vy = step;
    }
    if (key == GLFW_KEY_S) {
        vy = -step;
    }
    if (key == GLFW_KEY_A) {
        vx = -step;
    }
    if (key == GLFW_KEY_D) {
        vx = step;
    }
}

void framebuffer_size_callback(GLFWwindow* window, int w, int h)
{

   
}
