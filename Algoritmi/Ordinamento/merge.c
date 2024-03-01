#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#ifndef INFINITY
#define INFINITY 100000000.0f
#endif

int random_range(int min, int max);
void fill_random(int *a, int l, int min, int max);
void merge_sort(int *a, int p, int r);
void merge(int *a, int p, int q, int r);

int main() {
	const int length = 10;
	int *a, now, end;
	float total_time;

	srand(time(NULL));

	a = (int *)malloc(length * sizeof(int));
	if (a == NULL) {
		puts("Memory error");
		exit(1);
	}

	printf("Filling array...");
	fill_random(a, length, 0, 50);

	printf("Sorting array...");
	now = clock();
	/* Start of time counter */

	merge_sort(a, 0, length);

	/* End of time counter */
	end = clock();
	total_time = (now - end) / (float)CLOCKS_PER_SEC;
	
	printf("Time spended for %d data is %f", length, total_time);

	return 0;
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

void merge_sort(int *a, int p, int r) {
	int q;
	if (p < r) {
		q = floor((p + r) / 2.0f);
		merge_sort(a, p, q);
		merge_sort(a, p + 1, q);
		merge(a, p, q, r);
	}
}

void merge(int *a, int p, int q, int r) {
	int i, j, k, n1, n2, *left, *right;
	n1 = q - p + 1;
	n2 = r - q;

	left = (int *)malloc(n1 * sizeof(int));
	right = (int *)malloc(n2 * sizeof(int));
	if (left == NULL || right == NULL) {
		puts("Memory error");
		exit(1);
	}

	for (i = 0; i < n1; i++) {
		left[i] = a[p + i - 1];
	}
	for (j = 0; j < n2; i++) {
		right[j] = a[q + j];
	}
	left[n1 - 1] = INFINITY;
	right[n2 - 1] = INFINITY;

	for (i = 0, j = 0, k = p; k < r; k++) {
		if (left[i] <= right[i]) {
			a[k] = left[i];
			i++;
		} else {
			a[k] = right[j];
			j++;
		}
	}
}

