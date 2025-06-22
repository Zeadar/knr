#pragma once

#include <stddef.h>
#include <stdlib.h>
#include "types.h"
#define GRIDSIZE sizeof(size_t)
//4096: assumed page size
#define BYTESTEPSIZE 4096
#define STEPSIZE (BYTESTEPSIZE / GRIDSIZE)
#define slice_new(data_t) slice_create(sizeof(data_t))
#define slice_get(data_t, slice, index) *(data_t *)slice_get_ptr(slice, index)

typedef struct slice {
    size_t *begin;
    size_t *head;
    size_t *end;
    size_t width;
} Slice;

typedef ptrdiff_t slice_index;

Slice slice_create(size_t byte_width) {
    size_t width = byte_width / GRIDSIZE < 1 ? 1 : byte_width / GRIDSIZE;
    size_t init_size = STEPSIZE + (width / STEPSIZE) * STEPSIZE;

    Slice slice = {
        .begin = malloc(init_size * GRIDSIZE),
        .head = slice.begin,
        .end = slice.begin + init_size,
        .width = width,
    };

    return slice;
}

void slice_destroy(Slice *slice) {
    free(slice->begin);
    slice->begin = 0;
    slice->head = 0;
    slice->end = 0;
    slice->width = 0;
}

slice_index slice_size(const Slice *slice) {
    return (slice->head - slice->begin) / slice->width;
}

slice_index slice_room(const Slice *slice) {
    return (slice->end - slice->begin) / slice->width;
}

void slice_check_grow(Slice *slice) {
    if (slice->head + slice->width < slice->end)
        return;

    size_t used_size = slice->head - slice->begin;
    size_t grow_size =
        slice->end - slice->begin + STEPSIZE +
        (slice->width / STEPSIZE) * STEPSIZE;

    size_t *new = realloc(slice->begin, grow_size * GRIDSIZE);

    slice->begin = new;
    slice->head = slice->begin + used_size;
    slice->end = slice->begin + grow_size;
}

s8 slice_ptr_in_bounds(const Slice *slice, void *ptr) {
    size_t *find_me = ptr;
    return find_me >= slice->begin && find_me < slice->head;
}

slice_index slice_find(const Slice *slice, void *ptr) {
    size_t *find_me = ptr;
    return (find_me - slice->begin) / slice->width;
}

s8 slice_index_in_bounds(const Slice *slice, slice_index index) {
    return index < slice_size(slice) && index >= 0;
}

void *slice_get_ptr(const Slice *slice, slice_index index) {

    return slice->begin + index * slice->width;
}

void *slice_allocate(Slice *slice) {
    slice_check_grow(slice);

    slice->head += slice->width;
    return slice->head - slice->width;
}

slice_index slice_push(Slice *slice, const void *data) {
    slice_check_grow(slice);

    const size_t *read_head = data;
    size_t *write_head = slice->head;
    size_t widths_left = slice->width;

    while (widths_left--)
        *write_head++ = *read_head++;

    slice->head += slice->width;

    return (slice->head - slice->begin - slice->width) / slice->width;
}

void slice_remove(Slice *slice, slice_index index) {
    slice_index size = slice_size(slice);

    if (index != size - 1) {
        size_t *here = slice->begin + index * slice->width;
        size_t *last = slice->head - slice->width;
        size_t widths_left = slice->width;

        while (widths_left--)
            *here++ = *last++;
    }

    slice->head = slice->head - slice->width;
}

void slice_serial_remove(Slice *slice, slice_index index) {
    slice_index item_size = slice_size(slice);

    if (index >= item_size || index < 0)
        return;

    if (index != item_size - 1) {
        size_t *here = slice->begin + index * slice->width;
        size_t *next = slice->begin + (index + 1) * slice->width;

        while (next != slice->head)
            *here++ = *next++;
    }

    slice->head = slice->head - slice->width;
}

void slice_replace(Slice *slice, slice_index index, void *data) {
    size_t widths_left = slice->width;
    size_t *read_head = data;
    size_t *write_head = slice_get_ptr(slice, index);

    while (widths_left--)
        *write_head++ = *read_head++;
}

void slice_foreach(Slice *slice, void (*fn)(void *)) {
    slice_index size = slice_size(slice);
    slice_index index;

    for (index = 0; index != size; ++index)
        fn(slice->begin + index * slice->width);
}

void slice_qsort(Slice *slice,
                 int (*compare_fn)(const void *a, const void *b)) {
    qsort(slice->begin, slice_size(slice),
          slice->width * sizeof(size_t), compare_fn);
}
