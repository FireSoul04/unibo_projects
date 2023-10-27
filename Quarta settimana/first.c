#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/**
 * Funzione per generare un numero casuale in un range scelto
 * @param min Minimo numero che può essere generato
 * @param max Massimo numero che può essere generato
 * @returns Numero casuale
*/
int random(int min, int max) {
    return min + rand() % (max - min) + 1;
}

void print_array(int a[], int a_length) {
    for (int i = 0; i < a_length; i++) {
        printf("%d, ", a[i]);
    }
    printf("\n");
}

/**
 * Funzione per riempire un array con valori pseudo-casuali
 * @param a Array da riempire
*/
int* fill_array(int a[], int a_length, int min, int max) {
    for (int i = 0; i < a_length; i++) {
        a[i] = random(min, max);
    }
    return a;
}

/**
 * Funzione per ottenere l'intersezione con valori ripetuti
 * @param a Primo array da controllare
 * @param b Secondo array da controllare
 * @param inters Array dove salvo l'intersezione dei due array
*/
int* intersezione_r(int* a, int* b, int a_length, int b_length, int* inters_length) {
    int k = 0, length = 0, *inters;

    for (int i = 0; i < a_length; i++) {
        for (int j = 0; j < b_length; j++) {
            if (a[i] == b[j]) {
                length++;
            }
        }
    }
    inters = (int *) malloc(length * sizeof(int));

    for (int i = 0; i < a_length; i++) {
        for (int j = 0; j < b_length; j++) {
            if (a[i] == b[j]) {
                inters[k] = a[i];
                k++;
            }
        }
    }
    *inters_length = length;
    return inters;
}

/**
 * Funzione per ottenere l'intersezione con valori non ripetuti
 * @param a Primo array da controllare
 * @param b Secondo array da controllare
 * @param inters Array dove salvo l'intersezione dei due array
*/
int* intersezione_sr(int* a, int* b, int a_length, int b_length, int* inters_length) {
    int *inters, *test, length, k = 0;
    
    inters = intersezione_r(a, b, a_length, b_length, inters_length);

    length = *inters_length;
    test = (int *) malloc(length * sizeof(int));
    for (int i = 0; i < length; i++) {
        test[i] = -1;
    }

    for (int i = 0; i < length; i++) {
        for (int j = i; j < length; j++) {
            if (inters[i] == inters[j] && i == j){
                test[k] = inters[i];
            }
        }
        k++;
    }
    print_array(test, length);
    return inters;
}

int main() {
    int *arr1, *arr2, *arr_un, *arr_int, arr1_length, arr2_length, arr_un_length, arr_int_length = 0;

    printf("Inserisci le lunghezze degli array\n");

    printf("Array 1: ");
    scanf("%d", &arr1_length);
    fflush(stdin);
    printf("Array 2: ");
    scanf("%d", &arr2_length);
    fflush(stdin);

    arr_un_length = arr1_length + arr2_length;

    arr1 = (int *)malloc(arr1_length * sizeof(int));
    arr2 = (int *)malloc(arr2_length * sizeof(int));
    arr_un = (int *)malloc(arr_un_length * sizeof(int));

    srand(clock());

    arr1 = fill_array(arr1, arr1_length, 0, 10);
    arr2 = fill_array(arr2, arr2_length, 0, 5);

    printf("Valori array 1: ");
    print_array(arr1, arr1_length);
    printf("Valori array 2: ");
    print_array(arr2, arr2_length);

    arr_int = intersezione_sr(arr1, arr2, arr1_length, arr2_length, &arr_int_length);
    printf("Valori array int: ");
    print_array(arr_int, arr_int_length);

    return 0;
}