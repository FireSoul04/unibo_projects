// ProgettoI.cpp : Questo file contiene la funzione 'main', in cui inizia e termina l'esecuzione del programma.
//

#include <glad/glad.h>               // Loader per funzioni OpenGL (carica puntatori a funzioni OpenGL)
#include <GLFW/glfw3.h>              // Libreria per gestione finestre, input, context OpenGL
#include <ImGui\imgui.h>             // Libreria ImGui per GUI immediate mode
#include <ImGui\imgui_impl_glfw.h>  // Integrazione ImGui con GLFW (input e finestre)
#include <ImGui\imgui_impl_opengl3.h> // Integrazione ImGui con OpenGL3 (rendering)

#include <iostream>                  // Input/output standard C++
#include "gestione_Eventi.h"         // Header personalizzato per callback eventi (es. tastiera, mouse)
#include "Gui.h"                     // Header personalizzato per gestione interfaccia ImGui


// Variabile globale ImVec4 per colore di pulizia (RGBA)
ImVec4 clear_color = ImVec4(0.45f, 0.0f, 0.0f, 1.00f);

int main(void)
{
    GLFWwindow* window;

    /* Inizializza GLFW */
    if (!glfwInit())  // Se l’inizializzazione fallisce, esce dal programma con codice -1
        return -1;

    // Setta versioni OpenGL e profilo core (3.3 core profile)
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Abilita il double buffering per rendering fluido
    glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_TRUE);

    /* Crea la finestra con contesto OpenGL */
    window = glfwCreateWindow(900, 900, "Hello World", NULL, NULL);

    if (!window) // Controlla la creazione della finestra
    {
        std::cout << "Creazione Finestra Fallita!" << std::endl; // Se fallito, stampa errore
        glfwTerminate(); // Libera risorse GLFW
        return -1;  // Esce segnalando errore
    }

    /* Rende corrente il contesto OpenGL della finestra appena creata */
    glfwMakeContextCurrent(window);

    /* Carica i puntatori OpenGL tramite GLAD */
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Fallisce il caricamento dei puntatori alle  !" << std::endl;
        glfwTerminate(); // Libera risorse se fallisce
        return -1;
    }

    // Registra callback per eventi: tastiera, posizione mouse, click mouse, resize viewport
    glfwSetKeyCallback(window, key_callback);
    glfwSetCursorPosCallback(window, cursor_position_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    /* Inizializza ImGui con la finestra GLFW */
    Initialize_IMGUI(window);

    /* Loop principale finché la finestra non deve chiudersi */
    while (!glfwWindowShouldClose(window))
    {
        my_interface(); // Disegna l’interfaccia ImGui

        /* Imposta il colore di pulizia (background) */
        glClearColor(clear_color.x, clear_color.y, clear_color.z, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT); // Pulisce il buffer colore

        /* Renderizza la GUI ImGui */
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        /* Scambia i buffer (double buffering) per visualizzare il frame appena renderizzato */
        glfwSwapBuffers(window);

        /* Processa gli eventi input (tastiera, mouse, etc.) */
        glfwPollEvents();
    }

    /* Pulizia finale */
    close_GUI();               // Libera risorse ImGui
    glfwDestroyWindow(window); // Distrugge la finestra
    glfwTerminate();           // Termina GLFW e libera risorse residue

    return 0; // Uscita con successo
}
