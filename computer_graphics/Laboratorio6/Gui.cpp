#pragma once
// Garantisce che il file venga incluso una sola volta in fase di compilazione
#include <fstream>
#include "strutture.h"
#include <ImGui\imgui.h>           // Libreria core ImGui
#include <ImGui\imgui_impl_glfw.h> // Integrazione ImGui con GLFW (gestione finestra/input)
#include <ImGui\imgui_impl_opengl3.h> // Integrazione ImGui con OpenGL3 (rendering)
#include "lib.h"
#include "gestione_curve.h"
#include "inizializzazioni.h"
#include <math.h> // Libreria matematica standard C
#pragma warning(disable:4996)

extern ImVec4 clear_color;  // Colore di sfondo (RGBA), dichiarato esternamente
extern double mousex, mousey; // Coordinate del mouse, dichiarate esternamente
extern bool flag_wireframe;
extern int numRows, numCols;
extern int width, height;
extern int Mod, selected_point;
extern bool visualizzaTg, modTg;
extern bool riempi, visualizza_PC;
extern Curva curva;
extern float* t;
extern float Tens, Bias, Cont;
extern int param;
 
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

    ImGui::SetNextWindowPos(ImVec2(50, height*0.7)); // Imposta posizione finestra successiva (50, 1050)

    ImGui::Begin("Impostazioni Sfondo", NULL,  // Apre finestra "Impostazioni"
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
    ImGui::Text("Gestione dei punti");
    ImGui::RadioButton("Inserimento", &Mod, 0); ImGui::SameLine();
    ImGui::RadioButton("Modifica", &Mod, 1); ImGui::SameLine();
    ImGui::RadioButton("Elimina", &Mod, 2); ImGui::SameLine();
    ImGui::Checkbox("Wireframe", &flag_wireframe);
    ImGui::End(); // Chiude la finestra "Impostazioni"

    if (Mod == 0)  //Se sono in modalità inserimento, imposto che non c'è alcun punto selezionato
        selected_point = -1;

     
    ImGui::SetNextWindowPos(ImVec2(50, height*0.1), ImGuiCond_FirstUseEver);
    ImGui::Begin("Impostazioni Curva", NULL, ImGuiWindowFlags_AlwaysAutoResize); // Finestra con auto-resize  ); // Finestra con auto-resize  

    ImGui::RadioButton("Parametrizzazione Uniforme", &param, 0); ImGui::SameLine();
    ImGui::RadioButton("Parametrizzazione secondo le corde", &param, 1); 
    ImGui::Checkbox("Visualizza Poligono di Controllo", &visualizza_PC);
    ImGui::Checkbox("Renderizza", &riempi);  ImGui::SameLine();


    if (ImGui::Button("Chiudi Forma ")) {
        int vf = curva.CP.size() - 1;

        curva.CP[vf] = curva.CP[0];
        curva.Derivata[vf].x = dx(0, t, &curva);
        curva.Derivata[vf].y = dy(0, t, &curva);
        curva.Tens[vf] = curva.Tens[0];
        curva.Bias[vf] = curva.Bias[0];
        curva.Cont[vf] = curva.Cont[0];
        curva.colCP[vf] = curva.colCP[0];
    }

  

    ImGui::Text("Gestione Tangenti");
    ImGui::Checkbox("Visualizza Tangenti", &visualizzaTg);  ImGui::SameLine();
    ImGui::Checkbox("Modifica Tangenti", &modTg);
    if (modTg)  //Se modTg==True entra in modalità modifica
        Mod = 1;
   
    //Salvataggio dati   

    
    ImGui::Text("Salvataggio Dati");
    if (ImGui::Button("Salva")) {
        std::ofstream outputFile("mycurve.txt");
         if (outputFile.is_open()) {
            for (int i = 0; i < curva.CP.size(); i++)
                outputFile << curva.CP[i].x << "  " << curva.CP[i].y << "  " << curva.CP[i].z << "  " << curva.Tens[i] << "  " << curva.Bias[i] << "  " << curva.Cont[i] << std::endl;

            outputFile.close();
            std::cout << "Dati scritti con successo." << std::endl;
        }
    }
    ImGui::SameLine();

    //Apertura dile dai dati
    if (ImGui::Button("Apri")) {
        int i;
        struct Dati {
            float x;
            float y;
            float z;
            float Tens;
            float Bias;
            float Cont;
        };

        FILE* file = fopen("mycurve.txt", "r");
        if (file == NULL) {
            perror("Impossibile aprire il file");
        }

        // Vettore per memorizzare i dati
        struct Dati dati[1000]; // Supponiamo che ci siano al massimo 100 righe nel file

        int riga = 0;
        while (fscanf(file, "%f %f %f %f %f %f ", &dati[riga].x, &dati[riga].y, &dati[riga].z, &dati[riga].Tens, &dati[riga].Bias, &dati[riga].Cont) == 6) {
            // Incrementa l'indice della riga
            riga++;
            cout << riga << endl;
            // Puoi aggiungere un controllo qui per evitare il superamento dell'array dati
            if (riga >= 1000) {
                printf("Troppe righe nel file. L'array dati   stato completamente riempito.\n");
                break;
            }
        }
        // Chiudi il file
        fclose(file);
        
        for (int i = 0; i < riga; i++) {
            curva.CP.push_back(vec3(dati[i].x, dati[i].y, dati[i].z));
            curva.Tens.push_back(dati[i].Tens);
            curva.Bias.push_back(dati[i].Bias);
            curva.Cont.push_back(dati[i].Cont);
            curva.colCP.push_back(vec4(0.0, 0.0, 0.0, 1.0));
            curva.Derivata.push_back(vec3(0.0, 0.0, 0.0));
        
        }

        curva.ncp = curva.CP.size();

        UPDATE_VAO_DYNAMIC(&curva,true);
    }


    ImGui::End(); // Termina la finestra

    // Render ImGui
    ImGui::Render(); // Renderizza gli elementi dell'interfaccia ImGui

}
    

// Funzione per chiudere e pulire ImGui correttamente
void close_GUI() {
    ImGui_ImplOpenGL3_Shutdown();   // Rilascia risorse renderer OpenGL3
    ImGui_ImplGlfw_Shutdown();      // Rilascia risorse integrazione GLFW
    ImGui::DestroyContext();        // Distrugge contesto ImGui liberando memoria
}