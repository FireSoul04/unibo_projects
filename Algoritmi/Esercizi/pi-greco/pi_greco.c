#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

typedef struct Point2D {
    int x, y;
} Point2D;

int random_range(int min, int max);

int main(int argc, char *argv[]) {
    Point2D point, alt_point;
    int i, n_points, p_inside, radius, side;
    float vector_length, pi_test;

    if (argc != 3) {
        printf("Example of executing: %s <number_of_points> <circle_radius>", argv[0]);
        exit(EXIT_FAILURE);
    }

    srand(time(NULL));

    n_points = atoi(argv[1]);

    radius = atoi(argv[2]);
    side = radius * 2;

    p_inside = 0;

    system("clear");

    for (i = 0; i < n_points; i++) {
        point.x = random_range(0, side);
        point.y = random_range(0, side);
        alt_point.x = point.x - radius;
        alt_point.y = point.y - radius;

        vector_length = (int)sqrt((alt_point.x * alt_point.x) + (alt_point.y * alt_point.y));
        if (vector_length < radius) {
            p_inside++;
        }
    }


    pi_test = (p_inside / (float)n_points) * 4;
    printf("Inside square: %d, inside circle: %d, PI: %f", n_points - p_inside, p_inside, pi_test);
    getchar();
    system("clear");

    return 0;
}

int random_range(int min, int max) {
    int r = rand() % (max - min + 1) + min;
    return r;
}