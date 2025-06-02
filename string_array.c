#pragma once

#include <stdlib.h>
#include <string.h>
#include "types.h"

#define STEP 4096

typedef struct string_array {
    char *ptr;
    u64 head;
    u64 end;
} sarray;

sarray sarray_create() {
    sarray temp = {
        .ptr = malloc(STEP),
        .head = 0,
        .end = STEP,
    };

    return temp;
}

char *sarray_get(sarray *sarray, u64 index) {
    return sarray->ptr + index;
}

u64 sarray_push(sarray *sarray, char *c) {
    u64 bytes = strlen(c) + 1;

    if (bytes + sarray->head >= sarray->end)
        sarray->ptr =
            realloc(sarray->ptr,
                    sarray->end + STEP + (bytes / STEP) * STEP);

    char *head = sarray->ptr + sarray->head;

    while (*c != '\0')
        *head++ = *c++;

    *head++ = '\0';

    sarray->head += bytes;

    return sarray->head - bytes;
}

void sarray_destroy(sarray *sarray) {
    free(sarray->ptr);
    sarray->ptr = 0;
    sarray->head = 0;
    sarray->end = 0;
}
