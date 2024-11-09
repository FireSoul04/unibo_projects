#define HOURS_TO_SECONDS 3600
#define HOURS_TO_MINUTES 60
#define MINUTES_TO_SECONDS 60

int time_to_seconds(int h, int m, int s) {
    return h * HOURS_TO_SECONDS + m * MINUTES_TO_SECONDS + s;
}

float time_to_minutes(int h, int m, int s) {
    return (float)h * HOURS_TO_MINUTES + m + s / MINUTES_TO_SECONDS;
}

float time_to_hours(int h, int m, int s) {
    return (float)h + m / HOURS_TO_MINUTES + s / HOURS_TO_SECONDS;
}

int sum_time(int h1, int m1, int s1, int h2, int m2, int s2) {
    return time_to_seconds(h1, m1, s1) + time_to_seconds(h2, m2, s2);
}

int difference_time(int h1, int m1, int s1, int h2, int m2, int s2) {
    return time_to_seconds(h1, m1, s1) - time_to_seconds(h2, m2, s2);
}

int max_time(int h1, int m1, int s1, int h2, int m2, int s2) {
    int time1 = time_to_seconds(h1, m1, s1), time2 = time_to_seconds(h2, m2, s2);
    if (time1 >= time2) {
        return time1;
    } else if (time1 < time2) {
        return time2;
    }
}

int min_time(int h1, int m1, int s1, int h2, int m2, int s2) {
    int time1 = time_to_seconds(h1, m1, s1), time2 = time_to_seconds(h2, m2, s2);
    if (time1 <= time2) {
        return time1;
    } else if (time1 > time2) {
        return time2;
    }
}