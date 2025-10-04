#pragma once
// Garantisce che il file venga incluso una sola volta in fase di compilazione

#include <ImGui/imgui.h>           // Libreria core ImGui
#include <ImGui/imgui_impl_glfw.h> // Integrazione ImGui con GLFW (gestione finestra/input)
#include <ImGui/imgui_impl_opengl3.h> // Integrazione ImGui con OpenGL3 (rendering)

#include <math.h> // Libreria matematica standard C
#include <string>

extern ImVec4 clear_color;  // Colore di sfondo (RGBA), dichiarato esternamente
extern ImVec2 guiVertices[];
extern ImVec4 guiColors[];
extern double mousex, mousey; // Coordinate del mouse, dichiarate esternamente

float positionx, positiony; // Variabili per posizione editabili
float my_float = 0.0f;      // Valore float per input utente con inizializzazione a 0
int my_int = 0;             // Valore intero per input utente
bool flag1, flag2;          // Flag booleani per checkbox

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

    ImGui::SetNextWindowPos(ImVec2(50, 600)); // Imposta posizione finestra successiva (50, 800)

    ImGui::Begin("Impostazioni", NULL,  // Apre finestra "Impostazioni"
        ImGuiWindowFlags_NoResize |      // Impedisce ridimensionamento utente
        ImGuiWindowFlags_AlwaysAutoResize | // Ridimensionamento automatico al contenuto
        ImGuiWindowFlags_NoBackground |  // Sfondo trasparente
        ImGuiWindowFlags_NoTitleBar |    // Nasconde barra titolo
        ImGuiWindowFlags_NoMove           // Impedisce lo spostamento finestra
    );
    /*
    I flag sono valori interi con un solo bit attivato; combinati col bitwise OR
    abilitano più opzioni contemporaneamente. ImGui controlla quali flag sono attivi
    con operazioni bit a bit per definire il comportamento finestra.
    */

    ImGui::ColorEdit4("Colore di Sfondo", (float*)&clear_color); // Widget per modificare colore sfondo
    ImGui::Text("Coordinate Mouse relative alla finestra GLFW: (%.1f, %.1f)", mousex, mousey); // Mostra coordinate mouse
    
    ImGui::End(); // Chiude la finestra "Impostazioni"

    ImGui::Begin("Posizioni vertici", NULL,  // Apre finestra "Impostazioni"
        ImGuiWindowFlags_AlwaysAutoResize // Ridimensionamento automatico al contenuto
    );

    for (int i = 0; i < 3; i++) {
        std::string label = "vertex " + (i + 1);
        ImGui::SliderFloat(std::string(label + ".x").c_str(), &guiVertices[i].x, -1.0f, 1.0f);
        ImGui::SliderFloat(std::string(label + ".y").c_str(), &guiVertices[i].y, -1.0f, 1.0f);
    }

    ImGui::End();

    ImGui::Begin("Colori vertici", NULL,
        ImGuiWindowFlags_AlwaysAutoResize    
    );

    for (int i = 0; i < 3; i++) {
        std::string label = "vertex " + (i + 1);
        ImGui::SliderFloat(std::string(label + " red").c_str(), &guiColors[i].x, 0.0f, 1.0f);
        ImGui::SliderFloat(std::string(label + " blue").c_str(), &guiColors[i].y, 0.0f, 1.0f);
        ImGui::SliderFloat(std::string(label + " green").c_str(), &guiColors[i].z, 0.0f, 1.0f);
        ImGui::SliderFloat(std::string(label + " alpha").c_str(), &guiColors[i].w, 0.0f, 1.0f);
    }

    ImGui::End();

    ImGui::Render();   // Compila i dati UI per il rendering finale
}

// Funzione per chiudere e pulire ImGui correttamente
void close_GUI() {
    ImGui_ImplOpenGL3_Shutdown();   // Rilascia risorse renderer OpenGL3
    ImGui_ImplGlfw_Shutdown();      // Rilascia risorse integrazione GLFW
    ImGui::DestroyContext();        // Distrugge contesto ImGui liberando memoria
}
