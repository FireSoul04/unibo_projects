#include <stdio.h>

#ifdef _WIN32 /* valido sia per 32 che 64 bit */
	#define FFLUSH fflush(stdin)
#else
    void _fflush() {
        int ch;
        while ((ch = getchar()) != '\n' && ch != EOF) {}
    }

    #define FFLUSH _fflush()
#endif

#define length_of(array) (sizeof(array) / sizeof(array[0]))

int main() {
    int int_var;
    float float_var;
    double double_var;
    char char_var;
    int int_array[5] = { 10, 20, 30, 40, 50 };
    int array_length = length_of(int_array);

    int *int_ptr = &int_var;
    float *float_ptr = &float_var;
    double *double_ptr = &double_var;
    char *char_ptr = &char_var;
    int *int_array_ptr = int_array;

    // Aspetto che l'utente inserisca i valori
    printf("Inserisci un numero intero: ");
    scanf("%d", &int_var);
    FFLUSH;

    printf("Inserisci un float (numero con la virgola da massimo 7 cifre dopo la virgola): ");
    scanf("%f", &float_var);
    FFLUSH;
    
    printf("Inserisci un double (numero con la virgola da massimo 15 cifre dopo la virgola): ");
    scanf("%lf", &double_var);
    FFLUSH;
    
    printf("Inserisci un carattere: ");
    scanf("%c", &char_var);
    FFLUSH;

    printf("\n");
    printf("Valori scelti\nModo diretto (var): \n");
    // Stampo tutti i valori in modo diretto accedendo tramite variabile
    printf("Valore intero da variabile: %d\n", int_var);
    printf("Valore float da variabile: %.7f\n", float_var);
    printf("Valore double da variabile: %.15lf\n", double_var);
    printf("Valore carattere da variabile: %c\n", char_var);
    for (int i = 0; i < array_length; i++) {
        printf("Valore dell'array in posizione %d: %d\n", i, int_array[i]);
    }

    printf("\n");
    // Stampo tutti i valori in modo indiretto accedendo tramite puntatore
    printf("Modo indiretto (*ptr): \n");
    printf("Valore intero da puntatore: %d\n", *int_ptr);
    printf("Valore float da puntatore: %.7f\n", *float_ptr);
    printf("Valore double da puntatore: %.15lf\n", *double_ptr);
    printf("Valore carattere da puntatore: %c\n", *char_ptr);
    for (int i = 0; i < array_length; i++) {
        printf("Valore dell'array in posizione %d: %d\n", i, *(int_array_ptr + i));
    }

    printf("\n");
    // Stampo tutti gli indirizzi di memoria dei valori in modo diretto accedendo tramite variabile
    printf("Indirizzi di memoria dei valori scelti (&var): \n");
    printf("Indirizzo intero da variabile: %p\n", &int_var);
    printf("Indirizzo float da variabile: %p\n", &float_var);
    printf("Indirizzo double da variabile: %p\n", &double_var);
    printf("Indirizzo carattere da variabile: %p\n", &char_var);
    for (int i = 0; i < array_length; i++) {
        printf("Indirizzo del valore dell'array in posizione %d: %p\n", i, &int_array[i]);
    }

    printf("\n");
    // Stampo tutti gli indirizzi di memoria in modo indiretto accedendo tramite puntatore e stampo gli indirizzi dove sono salvati i puntatori
    printf("Indirizzi di memoria dei valori scelti (ptr e &ptr): \n");
    printf("Indirizzo intero da puntatore: %p, indirizzo del puntatore: %p\n", int_ptr, &int_ptr);
    printf("Indirizzo float da puntatore: %p, indirizzo del puntatore: %p\n", float_ptr, &float_ptr);
    printf("Indirizzo double da puntatore: %p, indirizzo del puntatore: %p\n", double_ptr, &double_ptr);
    printf("Indirizzo carattere da puntatore: %p, indirizzo del puntatore: %p\n", char_ptr, &char_ptr);
    printf("indirizzo puntatore array: %p\n", &int_array_ptr);
    for (int i = 0; i < array_length; i++) {
        printf("Indirizzo del valore dell'array in posizione %d: %p\n", i, int_array_ptr + i);
    }

    // Modifico i valori per dimostrare che gli indirizzi di memoria non cambiano al variare dei valori delle variabili
    int_var = 7;
    float_var = 5.643f;
    double_var = 4.213664;
    char_var = 'h';
    for (int i = 0; i < array_length; i++) {
        int_array[i] = (i + 1) * 5;
    }

    printf("\n");
    printf("Cambio i valori. Notare che gli indirizzi non cambiano nonostante i valori sono cambiati\n");
    printf("Modo diretto (var): \n");
    // Stampo tutti i valori in modo diretto accedendo tramite variabile
    printf("Valore intero da variabile: %d\n", int_var);
    printf("Valore float da variabile: %.7f\n", float_var);
    printf("Valore double da variabile: %.15lf\n", double_var);
    printf("Valore carattere da variabile: %c\n", char_var);
    for (int i = 0; i < array_length; i++) {
        printf("Valore dell'array in posizione %d: %d\n", i, int_array[i]);
    }

    printf("\n");
    // Stampo tutti i valori in modo indiretto accedendo tramite puntatore
    printf("Modo indiretto (*ptr): \n");
    printf("Valore intero da puntatore: %d\n", *int_ptr);
    printf("Valore float da puntatore: %.7f\n", *float_ptr);
    printf("Valore double da puntatore: %.15lf\n", *double_ptr);
    printf("Valore carattere da puntatore: %c\n", *char_ptr);
    for (int i = 0; i < array_length; i++) {
        printf("Valore dell'array in posizione %d: %d\n", i, *(int_array_ptr + i));
    }

    printf("\n");
    // Stampo tutti gli indirizzi di memoria dei valori in modo diretto accedendo tramite variabile
    printf("Indirizzi di memoria dei valori scelti (&var): \n");
    printf("Indirizzo intero da variabile: %p\n", &int_var);
    printf("Indirizzo float da variabile: %p\n", &float_var);
    printf("Indirizzo double da variabile: %p\n", &double_var);
    printf("Indirizzo carattere da variabile: %p\n", &char_var);
    for (int i = 0; i < array_length; i++) {
        printf("Indirizzo del valore dell'array in posizione %d: %p\n", i, &int_array[i]);
    }

    printf("\n");
    // Stampo tutti gli indirizzi di memoria in modo indiretto accedendo tramite puntatore e stampo gli indirizzi dove sono salvati i puntatori
    printf("Indirizzi di memoria dei valori scelti (ptr e &ptr): \n");
    printf("Indirizzo intero da puntatore: %p, indirizzo del puntatore: %p\n", int_ptr, &int_ptr);
    printf("Indirizzo float da puntatore: %p, indirizzo del puntatore: %p\n", float_ptr, &float_ptr);
    printf("Indirizzo double da puntatore: %p, indirizzo del puntatore: %p\n", double_ptr, &double_ptr);
    printf("Indirizzo carattere da puntatore: %p, indirizzo del puntatore: %p\n", char_ptr, &char_ptr);
    printf("indirizzo puntatore array: %p\n", &int_array_ptr);
    for (int i = 0; i < array_length; i++) {
        printf("Indirizzo del valore dell'array in posizione %d: %p\n", i, int_array_ptr + i);
    }

    return 0;
}