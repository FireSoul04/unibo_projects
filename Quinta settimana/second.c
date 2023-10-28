#include <stdio.h>
#include <string.h>

#ifdef _WIN32
    #define FFLUSH fflush(stdin)
#else
    void _fflush() {
        int ch;
        while ((ch = getchar()) != '\n' && ch != EOF) {}
    }

    #define FFLUSH _fflush()
#endif

#define MAX 30

unsigned int length_of_string(char* str) {
    unsigned int length = 0;

    for (int i = 0; str[i] != '\0'; i++) {
        length++;
    }

    return length;
}

/**
 * Converte una stringa senza utilizzare string.h
 * @param string stringa dove sostituire i caratteri
 * @param substring stringa contenente i caratteri da sostituire
*/
void convert_string1(char* str_ret, char* string, char* substring) {
    int k = 0,
        common_letters_counter = 0, // Contatore per controllare se trovo due caratteri di fila da convertire
        substring_length = length_of_string(substring); // Lunghezza della stringa contenente i caratteri da sostituire
        
    // Controllo ogni carattere della stringa
    for (int i = 0; string[i] != '\0'; i++) {
        // Controllo ogni carattere della prima stringa e finché sono uguali ai caratteri della seconda stringa aggiungo quanti caratteri hanno in comune
        if (string[i] == substring[0]) {
            for (int j = 0; substring[j] != '\0'; j++) {
                if (string[i + common_letters_counter] == substring[j]) { // Controllo se i caratteri corrispondono
                    common_letters_counter++; // Salvo quanti caratteri sono in comune
                } else {
                    common_letters_counter = 0;
                }
            }
        }

        // Controllo quando bisogna sostituire con un asterisco la sottostringa in comune
        if (common_letters_counter == substring_length) {
            common_letters_counter = 0;
            str_ret[k++] = '*';
            i += substring_length - 1; // Il ciclo controlla la posizione dopo le lettere in comune
        } else if (common_letters_counter == 0) {
            str_ret[k++] = string[i]; // Salvo nella stringa di ritorno i caratteri che non sono in comune
        }
    }
}

/**
 * Converte una stringa utilizzando string.h
 * @param string stringa dove sostituire i caratteri
 * @param substring stringa contenente i caratteri da sostituire
*/
void convert_string2(char* str_ret, char* string, char* substring) {
    int common_letters_counter = 0, // Contatore per controllare se trovo due caratteri di fila da convertire
        substring_length = length_of_string(substring); // Lunghezza della stringa contenente i caratteri da sostituire

    // Azzero la stringa di ritorno
    str_ret[0] = '\0';
    
    for (int i = 0; string[i] != '\0'; i++) {
        for (int j = 0; substring[j] != '\0'; j++) {
            // Controllo ogni sottostringa partendo dalla posizione i della stringa se combacia con la sottostringa
            if (strncmp(string + i + j, substring + j, substring_length - common_letters_counter) == 0) {
                common_letters_counter++; // Salvo quanti caratteri sono in comune
            } else {
                common_letters_counter = 0;
            }
        }

        // Controllo quando bisogna sostituire con un asterisco la sottostringa in comune
        if (common_letters_counter == substring_length) {
            strcat(str_ret, "*");
            common_letters_counter = 0;
            i += substring_length - 1; // Il ciclo controlla la posizione dopo le lettere in comune
        } else {
            strncat(str_ret, string + i, 1); // Salvo nella stringa di ritorno i caratteri che non sono in comune
        }
    }
}

int main() {
    char string[MAX] = "";
    char substring[MAX] = "";
    char string_sustitute[MAX] = "";

    printf("Programma per sostituire ogni volta che appare una sottostringa in una stringa con un *\n");

    printf("Stampare una stringa di massimo 30 caratteri:\n");
    gets(string);
    FFLUSH;

    printf("Stampare una sottostringa da sostituire con * nella stringa precedente di massimo 30 caratteri:\n");
    gets(substring);
    FFLUSH;
    
    convert_string1(string_sustitute, string, substring);
    printf("Stringa senza string.h: %s\n", string_sustitute);
    convert_string2(string_sustitute, string, substring);
    printf("Stringa con string.h:   %s\n", string_sustitute);
    return 0;
} 