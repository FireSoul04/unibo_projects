#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

/*#define DEBUG*/

int random_range(int min, int max);
void print_array(int *a, int l);
void fill_random(int *a, int l, int min, int max);

void bubble_sort(int *a, int l);

void merge_sort(int *a, int p, int r);
void merge(int *a, int p, int q, int r);

void swap(int *a, int *b);
int partition(int *a, int p, int r);
void quick_sort(int *a, int p, int r);
int r_partition(int *a, int p, int r);
void r_quick_sort(int *a, int p, int r);

int main(int argc, char *argv[]) {
	int *a, *c, i, max, now, end, length;
	float total_time;

	if (argc != 3) {
		puts("Two argument required");
		exit(EXIT_FAILURE);
	}

	length = atoi(argv[1]);
	max = atoi(argv[2]);

	srand(time(NULL));

	a = (int *)malloc(length * sizeof(int));
	c = (int *)malloc(length * sizeof(int));
	if (a == NULL || c == NULL) {
		puts("Memory error");
		exit(EXIT_FAILURE);
	}

	puts("Filling array...");
	fill_random(a, length, 0, max);

	for (i = 0; i < length; i++) {
		c[i] = a[i];
	}

	#ifdef DEBUG
	print_array(c, length);
	#endif

	puts("Sorting array...");
	now = (float)clock();
	/* Start of time counter */

	bubble_sort(c, length);

	/* End of time counter */
	end = (float)clock();
	total_time = (end - now) / (float)CLOCKS_PER_SEC;

	#ifdef DEBUG
	print_array(c, length);
	#endif
	
	printf("BUBBLE SORT: Time spended for %d data is %f\n", length, total_time);

	for (i = 0; i < length; i++) {
		c[i] = a[i];
	}

	#ifdef DEBUG
	print_array(c, length);
	#endif

	puts("Sorting array...");
	now = (float)clock();
	/* Start of time counter */

	merge_sort(c, 0, length - 1);

	/* End of time counter */
	end = (float)clock();
	total_time = (end - now) / (float)CLOCKS_PER_SEC;

	#ifdef DEBUG
	print_array(c, length);
	#endif
	
	printf("MERGE SORT: Time spended for %d data is %f\n", length, total_time);

	for (i = 0; i < length; i++) {
		c[i] = a[i];
	}

	#ifdef DEBUG
	print_array(c, length);
	#endif

	puts("Sorting array...");
	now = (float)clock();
	/* Start of time counter */

	quick_sort(a, 0, length - 1);

	/* End of time counter */
	end = (float)clock();
	total_time = (end - now) / (float)CLOCKS_PER_SEC;

	#ifdef DEBUG
	print_array(c, length);
	#endif
	
	printf("QUICK SORT: Time spended for %d data is %f\n", length, total_time);

	for (i = 0; i < length; i++) {
		c[i] = a[i];
	}

	#ifdef DEBUG
	print_array(c, length);
	#endif

	puts("Sorting array...");
	now = (float)clock();
	/* Start of time counter */

	r_quick_sort(a, 0, length - 1);

	/* End of time counter */
	end = (float)clock();
	total_time = (end - now) / (float)CLOCKS_PER_SEC;

	#ifdef DEBUG
	print_array(c, length);
	#endif
	
	printf("RAND QUICK SORT: Time spended for %d data is %f\n", length, total_time);

	free(a);
	free(c);

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

void bubble_sort(int *a, int l) {
	int i, sorted;
	do {
		sorted = 1;
		for (i = 0; i < l - 1; i++) {
			if (a[i] > a[i + 1]) {
				swap(&a[i], &a[i + 1]);
				sorted = 0;
			}
		}
	} while (!sorted);
}

void merge_sort(int *a, int p, int r) {
	int q;
	if (p < r) {
		q = (int)floor((p + r - 1) / 2.0f);
		merge_sort(a, p, q);
		merge_sort(a, q + 1, r);
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
		exit(EXIT_FAILURE);
	}

	for (i = 0; i < n1; i++) {
		left[i] = a[p + i];
	}
	for (j = 0; j < n2; j++) {
		right[j] = a[q + j + 1];
	}

	i = 0;
	j = 0;
	k = p;
	while (i < n1 && j < n2)  {
		if (left[i] <= right[j]) {
			a[k] = left[i];
			i++;
		} else {
			a[k] = right[j];
			j++;
		}
		k++;
	}

	while (i < n1) {
        a[k] = left[i];
        i++;
        k++;
    }
    while (j < n2) {
        a[k] = right[j];
        j++;
        k++;
    }
	free(right);
	free(left);
}

void swap(int *a, int *b) {
	int tmp;
	tmp = *a;
	*a = *b;
	*b = tmp;
}

int partition(int *a, int p, int r) {
	int x, i, j;
	x = a[r];
	i = p - 1;
	for (j = p; j <= r; j++) {
		if (a[j] < x) {
			i++;
			swap(&a[i], &a[j]);
		}
	}
	swap(&a[i + 1], &a[r]);
	return i + 1;
}

void quick_sort(int *a, int p, int r) {
	int q;
	if (p < r) {
		q = partition(a, p, r);
		quick_sort(a, p, q - 1);
		quick_sort(a, q + 1, r);
	}
}

int r_partition(int *a, int p, int r) {
	int i;
	i = random_range(p, r);
	swap(&a[r], &a[i]);
	return partition(a, p, r);
}

void r_quick_sort(int *a, int p, int r) {
	int q;
	if (p < r) {
		q = r_partition(a, p, r);
		r_quick_sort(a, p, q - 1);
		r_quick_sort(a, q + 1, r);
	}
}
