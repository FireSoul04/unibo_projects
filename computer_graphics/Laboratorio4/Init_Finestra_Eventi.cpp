
#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "gestione_interazioni.h"
extern GLFWwindow* window;
extern int height, width;

/* Create a windowed mode window and its OpenGL context */

int inizializza_window_context_events() {

    window = glfwCreateWindow(width, height, "Hello World", NULL, NULL);
    if (!window)
    {
        std::cout << "Failde to create the window !" << std::endl;
        glfwTerminate(); //Libera le risorse allcoata da glfwInit
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window); //crea il context corrente e lo associa a window. In opengl un rendering context � una macchina astati che memorizza tutte le informazioni necessarie e le risorse per il rendering grafico

    //verifica se la libreria GLAD � riuscita a caricare correttamente tutti i puntatori 
    // alle funzioni OpenGL necessarie.

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to load opengl function pointers !" << std::endl;
        glfwTerminate();
        return -1;
    }

        //Registrazione delle funzioni di callback che verranno chiamate quando si verificano
        //  determinati eventi

        //Implementa la chiusura dell'applicazione premendo il tasto Esc  e la modifica del colore dello sfondo con il tasto F2..
        glfwSetKeyCallback(window, key_callback);

        //Per visualizzare le coordinate del mouse che si muove sulla finestra grafica
         // Imposta la posizione iniziale del mouse
        int oX = 0;
        int oY = 0;

        // Imposta il cursore in posizione (0,0) e disabilita il movimento naturale
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        glfwSetCursorPos(window, oX, oY);
        //Riabilita il movimento naturale
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        //Per visualizzare le coordinate del mouse che si muove sulla finestra grafica
        glfwSetCursorPosCallback(window, cursor_position_callback);
       


        //per visualizzare le dimensioni della finestra ridimensionata

        glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

}