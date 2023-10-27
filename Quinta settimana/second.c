#include <stdio.h>
#include <string.h>

#define MAX 30

/*Scrivere un programma C che riceva in ingresso due parole inserite da tastiera.
Si consideri che ciascuna parola può contenere al massimo 30 caratteri.
Il programma deve essere case sensitive, cioè deve distinguere lettere
minuscole da lettere maiuscole e deve essere in grado anche di analizzare
numeri, simboli e segni di punteggiatura. Il programma deve sostituire
ogni occorrenza della seconda parola nella prima parola con il carattere ’*’.
Ad esempio, inserite le stringhe:

abchdfffchdchdtlchd

e:

chd

il programma deve visualizzare la stringa:

ab*fff**tl*

Scrivere due versioni: la prima deve ignorare la presenza della libreria
string.h e quindi dovete lavorare esplicitamente su ogni singolo carattere
delle stringhe. La seconda deve usare le funzioni della libreria string.h per
determinare la lunghezza e per ricercare sotto-stringhe all'interno di una stringa*/

unsigned int length_of_string(char* str) {
    unsigned int length = 0;

    for (int i = 0; str[i] != '\0'; i++) {
        length++;
    }

    return length;
}

/**
 * Converte una stringa senza utilizzare string.h
 * @param str1 stringa dove sostituire i caratteri
 * @param str2 stringa contenente i caratteri da sostituire
*/
void convert_string1(char* str_ret, char* str1, char* str2) {
    int k = 0,
        common_letters_counter = 0, // Contatore per controllare se trovo due caratteri di fila da convertire
        str2_length = length_of_string(str2); // Lunghezza della stringa contenente i caratteri da sostituire

    // Controllo ogni carattere della stringa
    for (int i = 0; str1[i] != '\0'; i++) {
        common_letters_counter = 0;

        for (int j = 0; str2[j] != '\0'; j++) {
            printf("%c==%c; ", str1[i], str2[j]);
            // if (str1[i + common_letters_counter++] != str2[j]) {
            //     common_letters_counter = 0;
            // }
        }
        printf("\n");

        if (common_letters_counter == str2_length) {
            str_ret[k++] = '*';
        } else if (common_letters_counter == 0) {
            str_ret[k++] = str1[i];
        }
    }
}

/**
 * Converte una stringa utilizzando string.h
 * @param str1 stringa dove sostituire i caratteri
 * @param str2 stringa contenente i caratteri da sostituire
*/
void convert_string2(char* str1, const char* str2) {
    
}

int main() {
    char str1[] = "abchdfffchdchdtlchd";
    char str2[] = "chdf";
    char str3[MAX];

    printf("STR1: %s\n", str1);
    printf("STR2: %s\n", str2);
    convert_string1(str3, str1, str2);
    printf("STR3: %s\n", str3);
    return 0;
}