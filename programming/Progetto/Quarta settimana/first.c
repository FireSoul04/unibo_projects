#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MIN_RANDOM 0
#define MAX_RANDOM 50

/**
 * Funzione per generare un numero casuale in un range scelto
 * @param min Minimo numero che può essere generato
 * @param max Massimo numero che può essere generato
 * @returns Numero casuale
*/
int random(int min, int max) {
    return min + rand() % (max - min) + 1;
}

/**
 * Stampa tutti i valori di un array
 * @param a Array da stampare
 * @param a_length Lunghezza dell'array
*/
void print_array(int* a, int a_length) {
    for (int i = 0; i < a_length; i++) {
        printf("%d, ", a[i]);
    }
    printf("\n");
}

/**
 * Stampa tutti gli indirizzi di memoria dei valori di un array
 * @param a Array da stampare
 * @param a_length Lunghezza dell'array
*/
void print_array_addresses(int* a, int a_length) {
    for (int i = 0; i < a_length; i++) {
        printf("%p, ", &a[i]);
    }
    printf("\n");
}

/**
 * Funzione per riempire un array con valori pseudo-casuali
 * @param a Array da riempire
 * @param a_length Lunghezza dell'array
 * @returns Array riempito
*/
int* fill_array_random(int* a, int a_length) {
    for (int i = 0; i < a_length; i++) {
        a[i] = random(MIN_RANDOM, MAX_RANDOM);
    }
    return a;
}

/**
 * Funzione per riempire un array con valori pseudo-casuali
 * @param a Array da riempire
 * @param a_length Lunghezza dell'array
 * @returns Array riempito
*/
int* fill_array(int* a, int a_length) {
    for (int i = 0; i < a_length; i++) {
        scanf("%d", &a[i]);
        fflush(stdin);
    }
    return a;
}

/**
 * Funzione per ottenere l'intersezione di due array con valori ripetuti
 * @param a Primo array da controllare
 * @param b Secondo array da controllare
 * @param a_length Lunghezza primo array
 * @param b_length Lunghezza secondo array
 * @param inters_length Lunghezza array intersezione
 * @returns Array con l'intersezione dei due array
*/
int* intersection(int* a, int* b, int a_length, int b_length, int* inters_length) {
    int k = 0, length = 0, *a_intersection;

    // Calcolo quanti valori bisogna salvare nell'array
    for (int i = 0; i < a_length; i++) {
        for (int j = 0; j < b_length; j++) {
            if (a[i] == b[j]) {
                length++;
            }
        }
    }

    if (length > 0) {
        // Creo l'array con la lunghezza appena calcolata
        a_intersection = (int *) malloc(length * sizeof(int));

        // Ottengo l'intersezione dei due array
        for (int i = 0; i < a_length; i++) {
            for (int j = 0; j < b_length; j++) {
                if (a[i] == b[j]) {
                    a_intersection[k] = a[i];
                    k++;
                }
            }
        }
    }

    // Salvo la lunghezza dell'array che ritorno
    *inters_length = length;

    return a_intersection;
}

/**
 * Funzione per ottenere l'intersezione di due array con valori non ripetuti
 * @param a Primo array da controllare
 * @param b Secondo array da controllare
 * @param a_length Lunghezza primo array
 * @param b_length Lunghezza secondo array
 * @param inters_length Lunghezza array intersezione
 * @returns Array con l'intersezione dei due array
*/
int* intersection_without_repeats(int* a, int* b, int a_length, int b_length, int* inters_length) {
    int *a_intersection, length = 0;

    // Calcolo quanti valori bisogna salvare nell'array
    for (int i = 0; i < a_length; i++) {
        for (int j = 0; j < b_length; j++) {
            if (a[i] == b[j]) {
                length++;
            }
        }
    }

    // Creo un array con lunghezza passata come parametro e lo riempio con -1 per indicare quando il valore è stato riempito o no
    a_intersection = (int *) malloc(length * sizeof(int));

    if (length > 0) {
        for (int i = 0; i < length; i++) {
            a_intersection[i] = -1;
        }

        // Controllo le intersezioni e i casi in cui non si ripetono
        for (int i = 0; i < a_length; i++) {
            for (int j = 0; j < b_length; j++) {
                if (a[i] == b[j]) {
                    for (int k = 0; k < length; k++) {
                        // Controllo quando la casella è da riempire e se non è ripetuta
                        if (!(a_intersection[k] != -1 && a_intersection[k] != a[i])) {
                            a_intersection[k] = a[i];
                            break;
                        }
                    }
                }
            }
        }

        // Controllo quanto è lungo l'array di intersezioni senza ripetizioni (-1 indica che quella casella dell'array non è stata riempita con un valore)
        length = 0;
        while (a_intersection[length] != -1) {
            length++;
        }
    }

    // Salvo la lunghezza dell'array che ritorno
    *inters_length = length;

    return a_intersection;
}

/**
 * Funzione per ottenere l'unione di due array
 * @param a Primo array da controllare
 * @param b Secondo array da controllare
 * @param a_length Lunghezza primo array
 * @param b_length Lunghezza secondo array
 * @param union_length Lunghezza array unione
 * @returns Array con l'intersezione dei due array
*/
int* union_array(int* a, int* b, int a_length, int b_length, int* union_length) {
    int length = 0, *a_union;

    // Creo l'array che ha come lunghezza la somma delle lunghezze dei due array
    length = a_length + b_length;
    a_union = (int *) malloc(length * sizeof(int));

    // Ottengo l'intersezione dei due array
    for (int i = 0; i < a_length; i++) {
        a_union[i] = a[i];
    }
    int i = 0;
    for (int j = a_length; j < length; j++) {
        a_union[j] = b[i];
        i++;
    }

    // Salvo la lunghezza dell'array che ritorno
    *union_length = length;

    return a_union;
}

int main() {
    int *arr1, *arr2, // Array da confrontare
        *arr_un, // Array di unione
        *arr_int, // Array di intersezione
        arr1_length, arr2_length, // Lunghezza dei due array da confrontare
        arr_un_length, // Lunghezza dell'array unione
        arr_int_length = 0, // Lunghezza dell'array intersezione
        choice = 0; // Scelta dell'utente

    // Seed della funzione rand
    srand(time(NULL));

    printf("Inserisci le lunghezze degli array\n");

    // Chiedo le lunghezze degli array da confrontare all'utente
    printf("Array 1: ");
    scanf("%d", &arr1_length);
    fflush(stdin);
    printf("Array 2: ");
    scanf("%d", &arr2_length);
    fflush(stdin);

    // Alloco gli array in base alla lunghezza scelta dall'utente
    arr1 = (int *)malloc(arr1_length * sizeof(int));
    arr2 = (int *)malloc(arr2_length * sizeof(int));

    // Riempio il primo array con numeri scelti dall'utente e il secondo con numeri casuali
    arr1 = fill_array(arr1, arr1_length);
    arr2 = fill_array_random(arr2, arr2_length);

    // Stampo i valori dei due array
    printf("Valori array 1: ");
    print_array(arr1, arr1_length);
    printf("Valori array 2: ");
    print_array(arr2, arr2_length);

    // Attendo che l'utente metta o 0 o 1
    do {
        printf("Scegli se stampare l'array di intersezioni\n0: senza ripetizioni\n1: con ripetizioni\nScelta: ");
        choice = getchar() - '0';
    } while (choice < 0 || choice > 1);

    // Stampa array intersezione che rispetta la scelta dell'utente
    switch (choice) {
    case 0:
        arr_int = intersection_without_repeats(arr1, arr2, arr1_length, arr2_length, &arr_int_length);
        printf("Valori array intersezione senza ripetizioni: ");
        print_array(arr_int, arr_int_length);
        break;
    case 1:
        arr_int = intersection(arr1, arr2, arr1_length, arr2_length, &arr_int_length);
        printf("Valori array intersezione con ripetizioni: ");
        print_array(arr_int, arr_int_length);
        break;
    }

    // Stampa array unione
    arr_un = union_array(arr1, arr2, arr1_length, arr2_length, &arr_un_length);
    printf("Valori array unione: ");
    print_array(arr_un, arr_un_length);

    // Stampo la dimensione in byte degli array e tutti gli indirizzi di memoria dei loro elementi
    printf("Il primo array occupa %d byte\nIndirizzi degli elementi che occupano il primo array: ", arr1_length * sizeof(int));
    print_array_addresses(arr2, arr2_length);
    printf("Il secondo array occupa %d byte\nIndirizzi degli elementi che occupano il secondo array: ", arr2_length * sizeof(int));
    print_array_addresses(arr1, arr1_length);
    printf("L'array intersezione occupa %d byte\nIndirizzi degli elementi che occupano l'array intersezione: ", arr_int_length * sizeof(int));
    print_array_addresses(arr_int, arr_int_length);
    printf("L'array unione occupa %d byte\nIndirizzi degli elementi che occupano l'array unione: ", arr_un_length * sizeof(int));
    print_array_addresses(arr_un, arr_un_length);

    getchar();

    return 0;
}