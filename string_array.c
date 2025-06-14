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

typedef u64 str_index;

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

void sarray_check_grow(sarray *sarray, u64 bytes) {
    if (bytes + sarray->head < sarray->end)
        return;

    sarray->end += STEP + (bytes / STEP) * STEP;
    sarray->ptr = realloc(sarray->ptr, sarray->end);
}

char *sarray_allocate(sarray *sarray, u64 bytes, str_index *index) {
    sarray_check_grow(sarray, bytes);

    *index = sarray->head;
    sarray->head += bytes;
    return sarray->ptr + sarray->head - bytes;
}

str_index sarray_push(sarray *sarray, char *c) {
    u64 bytes = strlen(c) + 1;

    sarray_check_grow(sarray, bytes);

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
