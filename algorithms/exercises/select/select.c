#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int random_range(int min, int max);
void print_array(int *a, int l);
void fill_random(int *a, int l, int min, int max);

int selection_sort(int *a, int l, int i);
void merge_sort(int *a, int p, int r, int *buffer);
void merge(int *a, int p, int q, int r, int *buffer);

int quick_selection(int *a, int l, int i);

int main(int argc, char *argv[]) {
    int *a, *b, i, sel, max, length;
    clock_t start;
    float elapsed;

    if (argc != 3) {
        fprintf(stderr, "Usage %s <array-size> <max-rand>", argv[0]);
		exit(EXIT_FAILURE);
	}

    length = atoi(argv[1]);
    max = atoi(argv[2]);

	srand(time(NULL));

	a = (int *)malloc(length * sizeof(int));
	b = (int *)malloc(length * sizeof(int));
	if (a == NULL || b == NULL) {
		fprintf(stderr, "Memory error");
		exit(EXIT_FAILURE);
	}

	puts("Filling array...");
	fill_random(a, length, 0, max);

    for (i = 0; i < length; i++) {
        b[i] = a[i];
    }

    start = clock();

    sel = selection_sort(a, length, length / 2);

    elapsed = (clock() - start) / (float)CLOCKS_PER_SEC;
    printf("SELECTION SORT: Time elapsed: %f", elapsed);

    start = clock();
    


    elapsed = (clock() - start) / (float)CLOCKS_PER_SEC;
    printf("QUICK SELECTION: Time elapsed: %f", elapsed);

	free(a);

    return 0;
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

void merge_sort(int *a, int p, int r, int *buffer) {
	int q;
    if (p < r) {
        q = (int)((p + r) / 2);
        merge_sort(a, p, q, buffer);
        merge_sort(a, q + 1, r, buffer);
        merge(a, p, q, r, buffer);
    }
}

void merge(int *v, int p, int q, int r, int *buffer) {
    int i, j, k, n1, n2;
    n1 = q - p + 1;
    n2 = r - q;
    for (i = 0; i < n1 + n2; i++) {
		buffer[i] = v[p + i];
	}

    i = 0;
    j = n1;
    k = p;
    while (i < n1 && j < n1 + n2) {
        if (buffer[i] <= buffer[j]) {
            v[k] = buffer[i];
            i++;
        } else {
            v[k] = buffer[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        v[k] = buffer[i];
        i++;
        k++;
    }
    while (j < n2) {
        v[k] = buffer[j];
        j++;
        k++;
    }
}

int selection_sort(int *a, int l, int i) {
    int *buffer;
    buffer = (int*)malloc(l * sizeof(int));

    merge_sort(a, 0, l - 1, buffer);

    free(buffer);
    return a[i];
}

int quick_selection(int *a, int l, int i) {

    return 0;
}
