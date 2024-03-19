#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define N 2
#define MAX 500

int randab(int a, int b);
void generate_random(int a[N][N], int n, int min, int max);
void clear_mat(int a[N][N], int n);
void print_mat(int a[N][N], int n, int max);
void matrix_mul(int a[N][N], int b[N][N], int out[N][N], int n);
void matrix_add(int a[N][N], int b[N][N], int out[N][N], int n);
void matrix_sub(int a[N][N], int b[N][N], int out[N][N], int n);
void strassen(int a[N][N], int b[N][N], int out[N][N], int n);

int main(void) {
    clock_t now;
    float elapsed;
    int a[N][N], b[N][N], c[N][N];

    generate_random(a, N, 0, MAX);
    print_mat(a, N, log10(MAX));
    generate_random(b, N, 0, MAX);
    print_mat(b, N, log10(MAX));

    now = clock();
    matrix_mul(a, b, c, N);
    elapsed = (clock() - now) / (float)CLOCKS_PER_SEC;

    printf("Time elapsed mat_mul: %f\n", elapsed);

    now = clock();
    strassen(a, b, c, N);
    elapsed = (clock() - now) / (float)CLOCKS_PER_SEC;

    printf("Time elapsed strassen: %f\n", elapsed);

    return 0;
}

/* Restituisce un valore casuale compreso tra a e b (estremi inclusi) */
int randab(int a, int b) {
    return a + rand() % (b-a+1);
}

/* Genera valori casuali nell'array */
void generate_random(int a[N][N], int n, int min, int max) {
    int i, j;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            a[i][j] = randab(min, max);
        }
    }
}

void print_mat(int a[N][N], int n, int digits) {
    int i, j, k;
    for (i = 0; i < n; i++) {
        printf("[ ");
        for (j = 0; j < n; j++) {
            for (k = 0; k < digits - log10(a[i][j]); k++) {
                putchar(' ');
            }
            printf("%d ", a[i][j]);
        }
        puts("]");
    }
}

void clear_mat(int a[N][N], int n) {
    int i, j;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            a[i][j] = 0;
        }
    }
}

void matrix_mul(int a[N][N], int b[N][N], int out[N][N], int n) {
    int i, j, k;
    clear_mat(out, n);
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            out[i][j] = 0;
            for (k = 0; k < n; k++) {
                out[i][j] += a[i][k] * b[k][j];
            }
        }
    }
}

void strassen(int a[N][N], int b[N][N], int out[N][N], int n) {
    int m1, m2, m3, m4, m5, m6, m7;

    clear_mat(out, n);

    m1 = (a[0][0] + a[1][1]) * (b[0][0] + b[1][1]);
    m2 = (a[1][0] + a[1][1]) *  b[0][0];
    m3 = (b[0][1] - b[1][1]) *  a[0][0];
    m4 = (b[1][0] - b[0][0]) *  a[1][1];
    m5 = (a[0][0] + a[0][1]) *  b[1][1];
    m6 = (a[1][0] - a[0][0]) * (b[0][0] + b[0][1]);
    m7 = (a[0][1] - a[1][1]) * (b[1][0] + b[1][1]);

    out[0][0] = m1 + m4 - m5 + m7;
    out[0][1] = m3 + m5;
    out[1][0] = m2 + m4;
    out[1][1] = m1 - m2 + m3 + m6;
}