#include <stdio.h>

long double factorial(long double);

int main() {
    long double n;

    printf("Inserisci un numero intero positivo: ");
    scanf("%Lf", &n);

    printf("Fattoriale di %.0Lf e' %.0Lf.", n, factorial(n));
}

long double factorial(long double n) {
    if (n <= 1) {   
        return 1;
    }

    return n * factorial(n - 1);
}