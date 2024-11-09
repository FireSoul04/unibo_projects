#include <stdio.h>
#include <stdlib.h>

int main() {
    int sum = 0, length, *array;
    float avg;

    printf("Inserisci la lunghezza della struttura: ");
    scanf("%d", &length);

    array = (int*) malloc(sizeof(int) * length);
    for (int i = 0; i < length; i++) {
        printf("Inserisci un valore numerico: ");
        scanf("%d", &array[i]);
    }

    for (int i = 0; i < length; i++) {
        sum += array[i];
    }

    avg = (float)(sum / length);
    printf("La media e' %f\n", avg);
    system("pause");

    return 0;
}