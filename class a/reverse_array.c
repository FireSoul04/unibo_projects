#include <stdio.h>

void print_reverse(int *, size_t, int);
void print_array(int *, size_t, int);

int main() {
    int a[7] = { 5, 1, 2, 5, 2, 3, 4 };
    print_reverse(a, 7, 6);
    printf("\n");
    print_array(a, 7, 0);
}

void print_reverse(int *array, size_t length, int index) {
    if (index < 0) {
        return;
    }
    printf("%d; ", array[index]);
    print_reverse(array, length, index - 1);
}

void print_array(int *array, size_t length, int index) {
    if (index >= length) {
        return;
    }
    printf("%d; ", array[index]);
    print_array(array, length, index + 1);
}