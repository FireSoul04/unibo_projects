#include <stdio.h>
#include <string.h>

#define STRING_LENGTH 200

struct point2D {
    int val;         // Valore nel punto
    double x, y;     // Coordinate del punto
    double distance; // Distanza dal punto di test
} point2D_t;

// Funzione per leggere i dati del dataset
int read_data(FILE *dataset) {
    const char separator[2] = ",";
    
    // Apro il file in lettura
    dataset = fopen("./loan_data.csv", "r");

    if (dataset == NULL) {
        printf("Il dataset non è stato trovato...");
        return -1;
    }

    char data[STRING_LENGTH + 1], *token;

    // Salta la prima riga
    fgets(data, STRING_LENGTH + 1, dataset);

    // Legge tutti i dati riga per riga
    while (fgets(data, STRING_LENGTH + 1, dataset) != NULL) {
        // Gestisco ogni dato singolarmente
        token = strtok(data, separator);
        while (token != NULL) {
            

            token = strtok(NULL, separator);
        }
    }

    fclose(dataset);
}

int main() {
    FILE *dataset = NULL;
    if (read_data(dataset) == -1) {
        return -1;
    }

    return 0;
}