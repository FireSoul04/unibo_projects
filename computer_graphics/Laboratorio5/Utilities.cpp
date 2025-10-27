#pragma once
#include "lib.h"
#include "strutture.h"
#include <random>
extern int width, height;
extern GLuint IdProj, IdModel;
vector<Figura> proiettili;

vec2 randomPosition(int width, int height) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_real_distribution<> disX(0.0f, static_cast<float>(width));
    std::uniform_real_distribution<> disY(0.0f, static_cast<float>(height));
    return glm::vec2(disX(gen), disY(gen));
}

// Funzione per attivare uno shader e impostare le uniformi necessarie per la trasformazione e altri parametri
 // Parametri:
 // - shader_programId: ID del programma shader OpenGL da attivare
 // - projection: matrice di proiezione (glm::mat4) da passare allo shader
 // - model: matrice di trasformazione modello (mat4) da passare allo shader
 // - currentTime: valore float che rappresenta il tempo corrente (ad esempio per animazioni nello shader)
 // - resolution: vettore 2D (vec2) che indica la risoluzione del viewport o finestra

void usaShaderConUniforms(unsigned int shader_programId, glm::mat4& projection, mat4& model, float currentTime, vec2 resolution) {
    // Attiva il programma shader specificato
    glUseProgram(shader_programId);

    // Passa la matrice di proiezione alla uniform "IdProj"
    // 1 indica il numero di matrici, GL_FALSE significa che la matrice non deve essere trasposta
    // glm::value_ptr ritorna un puntatore ai dati della matrice in formato compatibile con OpenGL
    glUniformMatrix4fv(IdProj, 1, GL_FALSE, glm::value_ptr(projection));

    // Passa la matrice modello alla uniform "IdModel"
    glUniformMatrix4fv(IdModel, 1, GL_FALSE, glm::value_ptr(model));

    // Se la risoluzione è valida (componenti positive) passa la uniform "iResolution"
    // che comunemente rappresenta la dimensione della finestra in pixel nello shader
    if (resolution.x > 0.0f && resolution.y > 0.0f) {
        glUniform2f(glGetUniformLocation(shader_programId, "iResolution"), resolution.x, resolution.y);
    }

    // Se currentTime è positivo, passa la uniform "iTime"
    // Utilizzata spesso per animazioni legate al tempo nello shader
    if (currentTime > 0.0f) {
        glUniform1f(glGetUniformLocation(shader_programId, "iTime"), currentTime);
    }
}

void findBB(Figura* fig) {
    int n;
    n = fig->vertices.size();
    float minx = fig->vertices[0].x; // Assumiamo che il primo elemento sia il minimo iniziale
    float miny = fig->vertices[0].y; // Assumiamo che il primo elemento sia il minimo iniziale

    float maxx = fig->vertices[0].x; // Assumiamo che il primo elemento sia il massimo iniziale
    float maxy = fig->vertices[0].y; // Assumiamo che il primo elemento sia il massimo iniziale

    for (int i = 1; i < n; i++) {
        if (fig->vertices[i].x < minx) {
            minx = fig->vertices[i].x;
        }
        if (fig->vertices[i].x > maxx) {
            maxx = fig->vertices[i].x;
        }

        if (fig->vertices[i].y < miny) {
            miny = fig->vertices[i].y;
        }

        if (fig->vertices[i].y > maxy) {
            maxy = fig->vertices[i].y;
        }
    }
     
    fig->min_BB_obj=vec4(minx,miny,0.0,1.0);
    fig->max_BB_obj = vec4(maxx, maxy, 0.0,1.0);

}
// Aggiorna le coordinate del Bounding Box di una figura nel sistema di riferimento del mondo,
// applicando la matrice di modellazione alle coordinate locali.
// Parametri:
//   - fig: Puntatore alla struttura Figura il cui Bounding Box deve essere aggiornato.
void updateBB(Figura* fig) {
    // Trasforma direttamente le coordinate del Bounding Box locale nel sistema del mondo.
	fig->min_BB_w = fig->Model * fig->min_BB_obj;
	fig->max_BB_w = fig->Model * fig->max_BB_obj;
}

// Verifica se due oggetti di tipo Figura collidono utilizzando i loro Bounding Box nel sistema di riferimento del mondo.
// Parametri:
//   - obj1: Prima figura da controllare per la collisione.
//   - obj2: Seconda figura da controllare per la collisione.
// Restituisce:
//   - true se i Bounding Box delle due figure si intersecano, false altrimenti.
bool checkCollision(Figura obj1, Figura obj2) {
    // guardo collisioni su asse x
    
	bool collisionX = obj1.max_BB_w.x >= obj2.min_BB_w.x &&
        obj1.min_BB_w.x <= obj2.max_BB_w.x;

    // guardo collisioni su asse y

	bool collisionY = obj1.max_BB_w.y >= obj2.min_BB_w.y &&
        obj1.min_BB_w.y <= obj2.max_BB_w.y;

    //Si ha collisione se c'è collisione sia nella direzione x che nella direzione y

    return collisionX && collisionY;
}



// Funzione aggiorna tutti i proiettili attivi

void aggiornaProiettili(float deltaTime) {
    float vel_y_proiettile = 40.0f;
    /*auto& p : proiettili) è la sintassi del ciclo range-based for introdotta in C++11.
     auto& significa che il tipo di p viene dedotto automaticamente in base agli elementi di proiettili
     e che p è un riferimento (evitando copie).
     Questo consente di modificare gli elementi direttamente nel contenitore.*/
    for (auto& p : proiettili) {
        if (p.isalive) {
           //Modifica la posizione verticale del proiettile
			p.position.y += vel_y_proiettile * deltaTime;
            if (p.position.y > height - 100) {
                p.isalive = false;
            }
           //Aggiorna la matrice di modellazione del proiettile
            p.Model = translate(p.Model, vec3(0.0f, vel_y_proiettile * deltaTime, 0.0f));

           //Aggiorna il BB del proiettile
            updateBB(&p);
        }
    }
    // Rimuove i proiettili non più vivi
    /*Guarda tutti gli elementi dentro il contenitore proiettili.
     remove_if riordina i dati, porta in fondo quelli da eliminare, e restituisce un iteratore di fine nuova.*/
     //erase cancella concretamente gli elementi nel range passato.
    proiettili.erase(
        remove_if(
            proiettili.begin(), proiettili.end(),
            [](const Figura& p) {
                return !p.isalive; }
        ),
        proiettili.end());
}