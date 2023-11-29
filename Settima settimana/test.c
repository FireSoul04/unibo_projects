#include <stdbool.h>
#include <stdio.h>

#define LENGTH 7

void sort(int *ints, int length) {
    bool sorted;
    do {
        sorted = true;
        for (int i = 0; i < length - 1; i++) {
            if (ints[i] > ints[i + 1]) {
                int n = ints[i];
                ints[i] = ints[i + 1];
                ints[i + 1] = n;
                sorted = false;
            }
        }
    } while(!sorted);
}

int main() {
    int n[LENGTH] = { 5, 9, 2, 10, 4, 8, 2 };
    
    printf("Before sorting:\n");
    for (int i = 0; i < LENGTH; i++) {
        printf("%d ", n[i]);
    }
    printf("\n");
    sort(n, LENGTH);
    printf("After:\n");
    for (int i = 0; i < LENGTH; i++) {
        printf("%d ", n[i]);
    }
    return 0;
}