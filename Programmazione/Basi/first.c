#include <stdio.h>

int main() {
    int d,
        n1, n2, n3, n4, n5,
        m1, m2, m3, m4, m5,
        sum1, sum2, total;

    scanf("%1d", &d);
    scanf("%1d%1d%1d%1d%1d", &n1, &n2, &n3, &n4, &n5);
    scanf("%1d%1d%1d%1d%1d", &m1, &m2, &m3, &m4, &m5);

    sum1 = n1 + n3+ n5 + m2 + m4;
    sum2 = n2 + n4 + m1 + m3 + m5;

    total = sum1 * 3 + sum2;
    total = 9 - (total % 10);

    printf("%d", total);

    return 0;
}