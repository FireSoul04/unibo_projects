#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

/*#define DEBUG*/

int random_range(int min, int max);
void print_array(int *a, int l);
void fill_random(int *a, int l, int min, int max);

void bubble_sort(int *a, int l);

void merge_sort(int *a, int p, int r, int *buffer);
void merge(int *a, int p, int q, int r, int *buffer);

void swap(int *a, int *b);
int partition(int *a, int p, int r);
void quick_sort(int *a, int p, int r);
int r_partition(int *a, int p, int r);
void r_quick_sort(int *a, int p, int r);

int main(int argc, char *argv[]) {
	int *a, *c, *buffer, i, max, length;
	clock_t start, end;
	float total_time;

	if (argc != 3) {
		puts("Two argument required");
		exit(EXIT_FAILURE);
	}

	length = atoi(argv[1]);
	max = atoi(argv[2]);

	srand(time(NULL));

    buffer = (int*)malloc(length * sizeof(int));
	a = (int *)malloc(length * sizeof(int));
	c = (int *)malloc(length * sizeof(int));
	if (a == NULL || c == NULL || buffer == NULL) {
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
	start = (float)clock();
	/* Start of time counter */

	bubble_sort(c, length);

	/* End of time counter */
	end = (float)clock();
	total_time = (end - start) / (float)CLOCKS_PER_SEC;

	#ifdef DEBUG
	print_array(c, length);
	#endif
	
	printf("BUBBLE SORT: Time spended for %d data is %f\n", length, total_time);

	for (i = 0; i < length; i++) {
		c[i] = a[i];
	}

	puts("Sorting array...");
	start = (float)clock();
	/* Start of time counter */

	merge_sort(c, 0, length - 1, buffer);

	/* End of time counter */
	end = (float)clock();
	total_time = (end - start) / (float)CLOCKS_PER_SEC;

	#ifdef DEBUG
	print_array(c, length);
	#endif
	
	printf("MERGE SORT: Time spended for %d data is %f\n", length, total_time);
	
	for (i = 0; i < length; i++) {
		c[i] = a[i];
	}

	puts("Sorting array...");
	start = (float)clock();
	/* Start of time counter */

	quick_sort(a, 0, length - 1);

	/* End of time counter */
	end = (float)clock();
	total_time = (end - start) / (float)CLOCKS_PER_SEC;

	#ifdef DEBUG
	print_array(c, length);
	#endif
	
	printf("QUICK SORT: Time spended for %d data is %f\n", length, total_time);

	for (i = 0; i < length; i++) {
		c[i] = a[i];
	}

	puts("Sorting array...");
	start = (float)clock();
	/* Start of time counter */

	r_quick_sort(a, 0, length - 1);

	/* End of time counter */
	end = (float)clock();
	total_time = (end - start) / (float)CLOCKS_PER_SEC;

	#ifdef DEBUG
	print_array(c, length);
	#endif
	
	printf("RAND QUICK SORT: Time spended for %d data is %f\n", length, total_time);

	free(a);
	free(c);
    free(buffer);

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
	int i = random_range(p, r);
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
