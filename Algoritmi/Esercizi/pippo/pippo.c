#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 10

int compare(const void *pa, const void *pb);
int random_range(int min, int max);
void print_array(int *a, int l);
void fill_random(int *a, int l, int min, int max);

int pippo(int *v, int *w, int vl, int i, int j, int k);

int main() {
    int *v, *w, k = 7;
    v = (int *)malloc(MAX * sizeof(int));
	w = (int *)malloc(MAX * sizeof(int));
	if (v == NULL || w == NULL) {
		puts("Memory error");
		exit(EXIT_FAILURE);
	}

    srand(time(NULL));

    fill_random(v, MAX, 0, 10);
    fill_random(w, MAX, 0, 10);
    qsort(v, MAX, sizeof(int), compare);
    qsort(w, MAX, sizeof(int), compare);

    print_array(v, MAX);
    print_array(w, MAX);

    printf("Risultato: %d\n", pippo(v, w, MAX, 0, MAX - 1, k));

    free(v);
    free(w);

    return 0;
}

int compare(const void *pa, const void *pb) {
    int a, b;
    a = *(int *)pa;
    b = *(int *)pb;
    return a - b;
}

void print_array(int *a, int l) {
	int i;
	for (i = 0; i < l; i++) {
		printf("%d, ", a[i]);
	}
	puts("");	
}

int random_range(int min, int max) {
	int r = (rand() % (max - min + 1)) + min;
	return r;
}

void fill_random(int *a, int l, int min, int max) {
	int i;
	for (i = 0; i < l; i++) {
		a[i] = random_range(min, max);
	}
}

int pippo(int *v, int *w, int vl, int i, int j, int k) {
    int ret;
    if (i >= vl || j < 0) {
        return 0;
    } else if (v[i] + w[j] != k) {
        if (v[i] + w[j] > k) {
            ret = pippo(v, w, vl, i, j - 1, k);
        } else {
            ret = pippo(v, w, vl, i + 1, j, k);
        }
        return ret;
    } else {
        return 1;
    }
}