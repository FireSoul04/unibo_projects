#include <stdio.h>
#include <time.h>

int main() {
    while (1) {
        FILE* i = __acrt_iob_func(0);

        time_t now = time(NULL);
        while (time(NULL) - now < 1);

        printf("%x ", i);
    }

    return 0;
}