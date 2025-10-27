#pragma once
// Garantisce che il file venga incluso una sola volta in fase di compilazione

#include <ImGui\imgui.h>           // Libreria core ImGui
#include <ImGui\imgui_impl_glfw.h> // Integrazione ImGui con GLFW (gestione finestra/input)
#include <ImGui\imgui_impl_opengl3.h> // Integrazione ImGui con OpenGL3 (rendering)
#include "lib.h"
#include <math.h> // Libreria matematica standard C

extern ImVec4 clear_color;  // Colore di sfondo (RGBA), dichiarato esternamente
extern double mousex, mousey; // Coordinate del mouse, dichiarate esternamente
extern bool flag_wireframe;
extern bool show_bounding_boxes;
extern int numRows, numCols;
extern int width, height;
extern float h_update, w_update;
extern unsigned int selected_bk;
extern unsigned int programId, programId_BK, programId_BK1, programId_BK2, programId_BK3, programId_BK4, programId_BK5, programId_BK6, programId_BK7, programId_BK8;
extern unsigned int IdProj_BK, id_res_BK, IdModel_BK, id_time_BK;
int current_shader_index = 0;
// Funzione che inizializza ImGui con GLFW e OpenGL
void Initialize_IMGUI(GLFWwindow* window) {
    IMGUI_CHECKVERSION();               // Controlla compatibilità versione ImGui
    ImGui::CreateContext();             // Crea il contesto ImGui (necessario)
    ImGuiIO& io = ImGui::GetIO();       // Ottiene l’oggetto IO di ImGui (config e input)
    io.FontGlobalScale = 2.0f;          // Scala globale del font (doppio delle dimensioni)
    ImGui::StyleColorsDark();            // Imposta tema scuro predefinito
    
    // Inizializza l’integrazione con GLFW per OpenGL
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330 core"); // Inizializza renderer OpenGL3 con versione 330 core
}

// Funzione di rendering dell’interfaccia grafica per ogni frame
void my_interface()
{
    ImGui_ImplGlfw_NewFrame();          // Prepara frame nuovo per input GLFW
    ImGui_ImplOpenGL3_NewFrame();       // Prepara frame nuovo per rendering OpenGL3
    ImGui::NewFrame();                  // Inizia registrazione nuova UI frame

    ImGui::SetNextWindowPos(ImVec2(0, h_update*0.8)); // Imposta posizione finestra successiva (50, 1050)

    ImGui::Begin("Impostazioni Sfondo", NULL,  // Apre finestra "Impostazioni"
        ImGuiWindowFlags_NoResize |      // Impedisce ridimensionamento utente
        ImGuiWindowFlags_AlwaysAutoResize | // Ridimensionamento automatico al contenuto
        ImGuiWindowFlags_NoMove           // Impedisce lo spostamento finestra
    );
    /*
    I flag sono valori interi con un solo bit attivato; combinati col bitwise OR
    abilitano più opzioni contemporaneamente. ImGui controlla quali flag sono attivi
    con operazioni bit a bit per definire il comportamento finestra.
    */
   
    if (ImGui::RadioButton("Sfondo Semplice ", &current_shader_index, 0)) {
        // Opzionale: Logica specifica se lo shader 0 è selezionato
        selected_bk = programId;

    }
    ImGui::SameLine();
    // Shader 1
    if (ImGui::RadioButton("Gradiente ", &current_shader_index, 1)) {
        selected_bk = programId_BK;
    }
    ImGui::SameLine();
    // Shader 2
    if (ImGui::RadioButton("Pattern", &current_shader_index, 2)) {
        selected_bk = programId_BK1;
    }
    ImGui::SameLine();
    // Shader 3
    if (ImGui::RadioButton("Neon", &current_shader_index, 3)) {
        selected_bk = programId_BK2;
    }
    ImGui::SameLine();
    if (ImGui::RadioButton("Onde", &current_shader_index, 4)) {
        selected_bk = programId_BK3;
    }
    ImGui::SameLine();
    if (ImGui::RadioButton("Fiore ", &current_shader_index, 5)) {
        selected_bk = programId_BK4;
    }
    ImGui::SameLine();
    if (ImGui::RadioButton("Pioggia ", &current_shader_index, 6)) {
        selected_bk = programId_BK5;
    }
    ImGui::SameLine();
    if (ImGui::RadioButton("Cielo ed Alberi ", &current_shader_index, 7)) {
        selected_bk = programId_BK6;
    }
    ImGui::SameLine();
    if (ImGui::RadioButton("Onde e Nuvole ", &current_shader_index, 8)) {
        selected_bk = programId_BK7;
    }
    if (ImGui::RadioButton("Bicolore ", &current_shader_index, 9)) {
        selected_bk = programId_BK8;
    }

    // Ottiene la posizione della variabile uniforme "Projection" nel programma shader del background
    IdProj_BK = glGetUniformLocation(selected_bk, "Projection");

    // Ottiene la posizione della variabile uniforme "Model" nel programma shader del background
    IdModel_BK = glGetUniformLocation(selected_bk, "Model");

    // Ottiene la posizione della variabile uniforme "iResolution" (risoluzione viewport) nel programma shader del background
    id_res_BK = glGetUniformLocation(selected_bk, "iResolution");

    // Ottiene la posizione della variabile uniforme "iResolution" (risoluzione viewport) nel programma shader del background
    id_time_BK = glGetUniformLocation(selected_bk, "iTime");
    ImGui::Checkbox("Flag Wireframe", &flag_wireframe);
    ImGui::SameLine();
    ImGui::Checkbox("Flag Bounding Box", &show_bounding_boxes);
    ImGui::End(); // Chiude la finestra "Impostazioni"

     
    ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_FirstUseEver);
    ImGui::Begin("Impostazioni Scena",NULL, ImGuiWindowFlags_NoMove); // Finestra con auto-resize  ); // Finestra con auto-resize  
    ImGui::SliderInt("elementi per riga", &numCols, 1, 10);
    ImGui::SliderInt("elementi per colonna", &numRows, 1, 10);
    ImGui::End();
    
    ImGui::Render();   // Compila i dati UI per il rendering finale
}

// Funzione per chiudere e pulire ImGui correttamente
void close_GUI() {
    ImGui_ImplOpenGL3_Shutdown();   // Rilascia risorse renderer OpenGL3
    ImGui_ImplGlfw_Shutdown();      // Rilascia risorse integrazione GLFW
    ImGui::DestroyContext();        // Distrugge contesto ImGui liberando memoria
}