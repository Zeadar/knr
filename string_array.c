#pragma once

#include <stdlib.h>
#include <string.h>
#include "slice.c"

#define STEP 4096

typedef struct string_array {
    char *ptr;
    size_t head;
    size_t end;
    Slice table;
} Sarray;

typedef size_t str_index;

Sarray sarray_create() {
    Sarray sarray = {
        .ptr = malloc(STEP),
        .head = 0,
        .end = STEP,
        .table = slice_new(str_index),
    };

    return sarray;
}

char *sarray_get(Sarray *sarray, slice_index index) {
    return sarray->ptr + slice_get(str_index, &sarray->table, index);
}

slice_index sarray_size(Sarray *sarray) {
    return slice_size(&sarray->table);
}

void sarray_check_grow(Sarray *sarray, size_t bytes) {
    if (bytes + sarray->head < sarray->end)
        return;

    sarray->end += STEP + (bytes / STEP) * STEP;
    sarray->ptr = realloc(sarray->ptr, sarray->end);
}

slice_index sarray_push(Sarray *sarray, char *str) {
    size_t bytes = strlen(str) + 1;

    sarray_check_grow(sarray, bytes);

    char *head = sarray->ptr + sarray->head;

    while (*str != '\0')
        *head++ = *str++;

    *head++ = '\0';

    slice_index index = slice_push(&sarray->table, &sarray->head);
    sarray->head += bytes;

    return index;
}

void sarray_remove(Sarray *sarray, slice_index index) {
    char *culprit = sarray_get(sarray, index);
    size_t bytes = strlen(culprit) + 1;

    char *write = culprit;
    char *read = culprit + bytes;

    while (read != sarray->ptr + sarray->head) {
        *write = *read;

        if (*write == '\0') {
            str_index here = (write + 1) - sarray->ptr;
            slice_replace(&sarray->table, ++index, &here);
        }

        ++write;
        ++read;
    }

    sarray->head -= bytes;

    slice_remove(&sarray->table, index);
}

void sarray_destroy(Sarray *sarray) {
    free(sarray->ptr);
    sarray->ptr = 0;
    sarray->head = 0;
    sarray->end = 0;
    slice_destroy(&sarray->table);
}
