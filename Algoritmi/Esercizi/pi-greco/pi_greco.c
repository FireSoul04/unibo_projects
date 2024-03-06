#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

typedef struct Point2D {
    int x, y;
} Point2D;

int random_range(int min, int max);

int main(int argc, char *argv[]) {
    Point2D point;
    int i, j, n_points, p_inside, iterations;
    float radius;
    double vector_length, pi_test, pi_total, pi_avg;

    if (argc != 4) {
        printf("Example of executing: %s <number_of_points> <circle_radius> <iterations>", argv[0]);
        exit(EXIT_FAILURE);
    }
    srand(time(NULL));

    pi_total = 0.0f;
    n_points = atoi(argv[1]);
    radius = atof(argv[2]);
    iterations = atoi(argv[3]);
    for (i = 0; i < iterations; i++) {
        p_inside = 0;

        for (j = 0; j < n_points; j++) {
            point.x = random_range(-radius, radius);
            point.y = random_range(-radius, radius);

            vector_length = sqrt((point.x * point.x) + (point.y * point.y));
            if (vector_length < radius) {
                p_inside++;
            }
        }
        pi_test = (p_inside / (float)n_points) * 4.0f;
        pi_total += pi_test;
    }
    pi_avg = pi_total / (float)iterations;

    printf("Iterations: %d\n", iterations);
    printf("Circle range: %f, PI: %.15f", radius, pi_avg);

    return 0;
}

int random_range(int min, int max) {
    int r = min + (rand() / (float)RAND_MAX) * (max - min);
    return r;
}