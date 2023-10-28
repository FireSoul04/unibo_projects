#include <stdio.h>
#include <conio.h>
#include <ctype.h>

int main() {
    char c = ' '; // Carattere dell'utente
    // Contatore per ogni funzione di cytpe.h
    int alphaNums = 0,
        alphabetChars = 0,
        controlChars = 0,
        notControlChars = 0,
        digits = 0,
        graphChars = 0,
        lowerCaseChars = 0,
        upperCaseChars = 0,
        punctuationChars = 0,
        spaces = 0,
        hexDigits = 0;

    printf("Inserisci dei caratteri a piacere e concludi con #\n");
    do {
        // Chiedo all'utente un carattere
        c = getch();
        printf("%c", c);
        
        // Aumento il contatore associato ad ogni funzione della libreria ctype.h
        if (isalnum(c)) {
            alphaNums++;
        }
        if (isalpha(c)) {
            alphabetChars++;
        }
        if (iscntrl(c)) {
            controlChars++;
        }
        if (isprint(c)) {
            notControlChars++;
        }
        if (isdigit(c)) {
            digits++;
        }
        if (isgraph(c)) {
            graphChars++;
        }
        if (islower(c)) {
            lowerCaseChars++;
        }
        if (isupper(c)) {
            upperCaseChars++;
        } 
        if (ispunct(c)) {
            punctuationChars++;
        } 
        if (isspace(c)) {
            spaces++;
        }
        if (isxdigit(c)) {
            hexDigits++;
        }
    } while(c != '#'); // Concludo il ciclo quando l'utente inserisce #

    // Stampo i contatori delle funzioni
    printf("\nCaratteri alfanumerici: %d\n", alphaNums);
    printf("Caratteri dell'alfabeto: %d\n", alphabetChars);
    printf("Caratteri di controllo: %d\n", controlChars);
    printf("Caratteri non di controllo: %d\n", notControlChars);
    printf("Caratteri numerici decimali: %d\n", digits);
    printf("Caratteri grafici: %d\n", graphChars);
    printf("Caratteri dell'alfabeto minuscolo: %d\n", lowerCaseChars);
    printf("Caratteri dell'alfabeto maiuscolo: %d\n", upperCaseChars);
    printf("Caratteri simbolici: %d\n", punctuationChars);
    printf("Caratteri di spazio: %d\n", spaces);
    printf("Caratteri numerici esadecimali: %d\n", hexDigits);

    return 0;
}
