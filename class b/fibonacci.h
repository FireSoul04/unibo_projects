#include <stdio.h>

int fib_n(int n) {
    int fib_n = 1, fib_n1 = 1, fib_n2 = 0;
    if (n == 0) {
        printf("%d\n", fib_n);
        return 0;
    }
    printf("%d\n", 1);
    for (int i = 0; i < n; i++) {
        fib_n = fib_n1 + fib_n2;
        fib_n2 = fib_n1;
        fib_n1 = fib_n;
        printf("%d\n", fib_n);
    }
    return 0;
}

int fib_n_under_maxfn() {

    return 0;
}

int n_fib_n(int n) {

}