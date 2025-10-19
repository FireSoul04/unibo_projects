// ProgettoI.cpp : Questo file contiene la funzione 'main', in cui inizia e termina l'esecuzione del programma.
//

#include <glad/glad.h>               // Loader per funzioni OpenGL (carica puntatori a funzioni OpenGL)
#include <GLFW/glfw3.h>              // Libreria per gestione finestre, input, context OpenGL
#include <ImGui/imgui.h>             // Libreria ImGui per GUI immediate mode
#include <ImGui/imgui_impl_glfw.h>  // Integrazione ImGui con GLFW (input e finestre)
#include <ImGui/imgui_impl_opengl3.h> // Integrazione ImGui con OpenGL3 (rendering)
#include "ShaderMaker.h"
#include <iostream>                  // Input/output standard C++
#include "gestione_Eventi.h"         // Header personalizzato per callback eventi (es. tastiera, mouse)
#include "Gui.h"                     // Header personalizzato per gestione interfaccia ImGui


// Variabile globale ImVec4 per colore di pulizia (RGBA)
ImVec4 clear_color = ImVec4(0.45f, 0.0f, 0.0f, 1.00f);

void INIT_SHADER(void);
void INIT_VAO(void);

static unsigned int programId;

unsigned int VAO;
unsigned int VBO_VERTICES;
unsigned int VBO_COLORS;
unsigned int EBO;


//Vertici del triangolo nel sistema di coordinate normalizzate

float vertices[] = {
     -0.5f, -0.5f, 0.0f,
      0.5f, -0.5f, 0.0f,
     -0.5f,  0.5f, 0.0f,
      0.5f,  0.5f, 0.0f,
};

float colors[] = {
    1.0f, 0.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 1.0f, 1.0f,
    0.5f, 0.5f, 0.0f, 1.0f,
    0.0f, 0.5f, 0.5f, 1.0f,
};

unsigned int elements[] = {
    0, 1, 2,
    1, 2, 3
};

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

    const GLFWvidmode *return_struct = glfwGetVideoMode(glfwGetPrimaryMonitor());

    int height = return_struct->height;
    int width = return_struct->width;

    /* Crea la finestra con contesto OpenGL */
    window = glfwCreateWindow(width * 0.8f, height * 0.8f, "Hello World", NULL, NULL);

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
    INIT_SHADER();
    INIT_VAO();
    /* Loop principale finché la finestra non deve chiudersi */
    while (!glfwWindowShouldClose(window))
    {
        my_interface(); // Disegna l’interfaccia ImGui

        /* Imposta il colore di pulizia (background) */
        glClearColor(clear_color.x, clear_color.y, clear_color.z, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT); // Pulisce il buffer colore

        /* Renderizza la GUI ImGui */
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

       

        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
         
        /* Scambia i buffer (double buffering) per visualizzare il frame appena renderizzato */
        glfwSwapBuffers(window);

        /* Processa gli eventi input (tastiera, mouse, etc.) */
        glfwPollEvents();
    }

    /* Pulizia finale */
    close_GUI();               // Libera risorse ImGui
    glfwDestroyWindow(window); // Distrugge la finestra
    
    glDeleteProgram(programId);
    glDeleteBuffers(1, &VBO_VERTICES);
    glDeleteBuffers(1, &VBO_COLORS);
    glDeleteBuffers(1, &EBO);
    glDeleteVertexArrays(1, &VAO);
    glfwTerminate();           // Termina GLFW e libera risorse residue

    return 0; // Uscita con successo
}


void INIT_SHADER(void)
{
    // Controlla se ci sono errori OpenGL pendenti prima di iniziare
    // GlGetError restituisce il codice di errore corrente, se c'è uno ancora non gestito
    GLenum ErrorCheckValue = glGetError();

    // Percorso o nome del file contenente il codice del vertex shader
    char* vertexShader = (char*)"vertexShaderC.glsl";

    // Percorso o nome del file contenente il codice del fragment shader
    char* fragmentShader = (char*)"fragmentShaderC.glsl";

    // Utilizza una funzione esterna ShaderMaker::createProgram per compilare e linkare
    // i due shader a partire dai loro file sorgenti.
    // Restituisce l'ID del programma shader risultante.
    programId = ShaderMaker::createProgram(vertexShader, fragmentShader);

    // Imposta il programma shader creato come corrente nella pipeline OpenGL.
    // Tutte le operazioni di rendering useranno questo programma finché non cambierà.
    glUseProgram(programId);
}

void INIT_VAO(void)
{
    // Genero un VAO (Vertex Array Object) che conterrà la configurazione degli attributi
    // Parametri: (n, *arrays)
    // n = numero di VAO da generare
    //  &VAO: indirizzo della variabile dove OpenGL scrive l'ID del nuovo VBO.
    glGenVertexArrays(1, &VAO);

    // Effettuo il bind del VAO, attivandolo come oggetto array in uso
     // Parametro:
    //   VAO: identificatore del Vertex Array Object da usare.
    glBindVertexArray(VAO);

    // Genero un VBO (Vertex Buffer Object) che conterrà i dati dei vertici
    // Parametri:  
    // n = numero di VBO da generare
     // &VBO: indirizzo della variabile dove OpenGL scrive l'ID del nuovo VBO.
    glGenBuffers(1, &VBO_VERTICES);

    // Effettuo il bind del VBO, dichiarando che sarà un buffer di tipo ARRAY (vertex data)
    // Parametri: (target, buffer)
    // target = GL_ARRAY_BUFFER → significa buffer che conterrà vertici
    // buffer = ID del VBO
    glBindBuffer(GL_ARRAY_BUFFER, VBO_VERTICES);

    // Copio i dati dei vertici dalla RAM alla GPU
    // Parametri: (target, size, *data, usage)
    // target = GL_ARRAY_BUFFER
    // size = dimensione del buffer in byte (qui sizeof(vertices))
    // *data = puntatore ai dati in CPU (array vertices)
    // usage = GL_STATIC_DRAW → dati caricati una volta sola e usati molte volte in draw
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Configuro l'attributo posizione (attribute location 0 nel vertex shader)
    // glVertexAttribPointer specifica come leggere dal buffer i dati dell'attributo
    // Parametri: (index, size, type, normalized, stride, pointer)
    // index = 0 → posizione nel vertex shader (layout(location=0))
    // size = 3 → numero di componenti (x,y,z) per vertice
    // type = GL_FLOAT → tipo dei dati
    // normalized = GL_FALSE → non normalizzare
    // stride = distanza tra l’inizio di due vertici consecutivi in byte (7*sizeof(float))
    // pointer = offset iniziale nel buffer (0 → parte dall’inizio)
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    // Attivo l’attributo con location 0
    // Parametri: (index)
    // index = 0 → abilita l’uso dell’attributo posizione
    glEnableVertexAttribArray(0);

    glGenBuffers(1, &VBO_COLORS);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_COLORS);
    glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);

    // Configuro l'attributo colore (attribute location 1 nel vertex shader)
    // Parametri: (index, size, type, normalized, stride, pointer)
    // index = 1 → posizione nel vertex shader (layout(location=1))
    // size = 4 → numero di componenti (r,g,b,a) per vertice
    // type = GL_FLOAT → tipo dei dati
    // normalized = GL_FALSE
    // stride = passo tra un vertice e il successivo (7*sizeof(float))
    // pointer = offset di partenza: dopo i primi 3 float della posizione (3*sizeof(float))
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);

    // Attivo l’attributo con location 1
    glEnableVertexAttribArray(1);

    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);
}
