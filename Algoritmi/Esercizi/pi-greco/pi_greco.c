#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#ifndef M_PI
#define M_PI 3.14
#endif

typedef struct Point2D {
    int x, y;
} Point2D;

int random_range(int min, int max);

int main(int argc, char *argv[]) {
    Point2D *points;
    int i, n_points, p_inside, p_outside, radius, side, c_area;
    float pi_test;

    if (argc != 3) {
        puts("Two argument required");
        exit(EXIT_FAILURE);
    }

    srand(time(NULL));

    n_points = atoi(argv[1]);

    points = (Point2D *)malloc(n_points * sizeof(Point2D));

    radius = atoi(argv[2]);
    side = radius * 2;

    c_area = (int)(M_PI * radius * radius);

    p_inside = 0;
    p_outside = 0;

    for (i = 0; i < n_points; i++) {
        points[i].x = random_range(0, side);
        points[i].y = random_range(0, side);

        p_outside++;
        if (points[i].x * points[i].y <= c_area) {
            p_inside++;
        }
    }

    pi_test = p_outside / (float)p_inside;
    printf("%d, %d, %f", p_inside, p_outside, pi_test);

    return 0;
}

int random_range(int min, int max) {
    int r = rand() % (max - min) + min;
    return r;
}