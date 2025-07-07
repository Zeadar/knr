#pragma once

#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "slice.c"

#define STEP 4096
#define PADSIZE sizeof(size_t)

typedef struct string_array {
    char *ptr;
    size_t head;
    size_t end;
    Slice table;
} Sarray;

typedef size_t str_index;

static size_t padsize(size_t bytesize) {
    return (bytesize + PADSIZE - 1) & ~(PADSIZE - 1);
}

Sarray sarray_create() {
    Sarray sarray = {
        .ptr = malloc(STEP),
        .head = 0,
        .end = STEP,
        .table = slice_new(str_index),
    };

    return sarray;
}

char *sarray_get(const Sarray *sarray, slice_index index) {
    return sarray->ptr + slice_get(str_index, &sarray->table, index);
}

slice_index sarray_size(const Sarray *sarray) {
    return slice_size(&sarray->table);
}

void sarray_check_grow(Sarray *sarray, size_t bytes) {
    if (bytes + sarray->head <= sarray->end)
        return;

    sarray->end += ((bytes + STEP - 1) & ~(STEP - 1));
    sarray->ptr = realloc(sarray->ptr, sarray->end);
}

slice_index sarray_push(Sarray *sarray, const char *str) {
    size_t bytes = strlen(str) + 1;

    sarray_check_grow(sarray, padsize(bytes));

    char *head = sarray->ptr + sarray->head;
    memcpy(head, str, bytes);

    slice_index index = slice_push(&sarray->table, &sarray->head);
    sarray->head += padsize(bytes);

    return index;
}

void sarray_remove(Sarray *sarray, slice_index index) {
    char *culprit = sarray_get(sarray, index);
    size_t bytes = padsize(strlen(culprit) + 1);

    memmove(culprit, culprit + bytes, sarray->head - bytes);
    sarray->head -= bytes;

    slice_remove(&sarray->table, index);

    while (index != slice_size(&sarray->table)) {
        str_index *si = slice_get_ptr(&sarray->table, index++);
        *si -= bytes;
    }
}

void sarray_destroy(Sarray *sarray) {
    free(sarray->ptr);
    sarray->ptr = 0;
    sarray->head = 0;
    sarray->end = 0;
    slice_destroy(&sarray->table);
}
