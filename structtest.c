#include <math.h>
#include <stdio.h>
#include <stdlib.h>

struct vec2 {
    double x;
    double y;
};

struct vec2 vec_constr(double x, double y) {
    struct vec2 temp = {.x = x,.y = y };
    return temp;
}

double vec2_len(const struct vec2 *v) {
    return sqrt(v->x * v->x + v->y * v->y);
}

struct vec2 vec_normalize(const struct vec2 *v) {
    double len = vec2_len(v);
    struct vec2 temp = {.x = 0,.y = 0 };

    if (len) {
        temp.x = v->x / len;
        temp.y = v->y / len;
    }

    return temp;
}

char *vec2_fmt(char str[], const struct vec2 *v) {
    sprintf(str, "{ %g, %g }", v->x, v->y);
    return str;
}

int main(int argc, char **argv) {
    char buffer[1024];

    double init_x = 0, init_y = 0;

    if (argc > 2) {
        init_x = atof(argv[1]);
        init_y = atof(argv[2]);
    }

    struct vec2 v1 = { init_x, init_y };
    double len = vec2_len(&v1);
    printf("Initial vector: %s\nwith length: %f\n", vec2_fmt(buffer, &v1),
           len);

    struct vec2 v1_norm = vec_normalize(&v1);
    len = vec2_len(&v1_norm);
    printf("Normalized vector: %s\nwith length: %f\n",
           vec2_fmt(buffer, &v1_norm), len);
}
