#pragma once

#include <stddef.h>
#include <stdlib.h>
#define GRIDSIZE sizeof(size_t)
//4096: assumed page size
#define BYTESTEP 4096
#define STEP (BYTESTEP / GRIDSIZE)
#define slice_new(data_t) slice_create(sizeof(data_t))
#define slice_get(data_t, slice, index) *(data_t *)slice_get_ptr(slice, index)

typedef struct slice {
    size_t *begin;
    size_t *head;
    size_t *end;
    size_t width;
} slice;

typedef ptrdiff_t slice_index;

slice slice_create(size_t byte_width) {
    size_t width = byte_width / GRIDSIZE < 1 ? 1 : byte_width / GRIDSIZE;
    size_t init_size = STEP + (width / STEP) * STEP;

    struct slice slice;
    slice.begin = malloc(init_size * GRIDSIZE);
    slice.head = slice.begin;
    slice.end = slice.begin + init_size;
    slice.width = width;

    return slice;
}

void slice_destroy(slice *slice) {
    free(slice->begin);
    slice->begin = 0;
    slice->head = 0;
    slice->end = 0;
    slice->width = 0;
}

slice_index slice_size(const slice *slice) {
    return (slice->head - slice->begin) / slice->width;
}

void slice_check_grow(slice *slice) {
    if (slice->head + slice->width < slice->end)
        return;

    size_t used_size = slice->head - slice->begin;
    size_t grow_size =
        slice->end - slice->begin + STEP + (slice->width / STEP) * STEP;

    size_t *new = realloc(slice->begin, grow_size * GRIDSIZE);

    slice->begin = new;
    slice->head = slice->begin + used_size;
    slice->end = slice->begin + grow_size;
}

slice_index slice_find(slice *slice, void *ptr) {
    size_t *find_me = ptr;

    if (find_me < slice->begin || find_me >= slice->head)
        return -1;

    return (find_me - slice->begin) / slice->width;
}

void *slice_allocate(slice *slice) {
    slice_check_grow(slice);

    slice->head += slice->width;
    return slice->head - slice->width;
}

slice_index slice_push(slice *slice, const void *data) {
    slice_check_grow(slice);

    const size_t *read_head = data;
    size_t *write_head = slice->head;
    size_t widths_left = slice->width;
    while (widths_left--)
        *write_head++ = *read_head++;

    slice->head += slice->width;

    return (slice->head - slice->begin - slice->width) / slice->width;
}

void slice_remove(slice *slice, slice_index index) {
    slice_index size = slice_size(slice);

    if (index >= size || index < 0)
        return;

    if (index != size - 1) {
        size_t *here = slice->begin + index * slice->width;
        size_t *last = slice->head - slice->width;
        size_t widths_left = slice->width;

        while (widths_left--)
            *here++ = *last++;
    }

    slice->head = slice->head - slice->width;
}

void slice_serial_remove(slice *slice, slice_index index) {
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


void *slice_get_ptr(const slice *slice, slice_index index) {
    if (index >= slice_size(slice) || index < 0)
        return 0;

    return slice->begin + index * slice->width;
}

void slice_replace(slice *slice, slice_index index, void *data) {
    size_t widths_left = slice->width;
    size_t *read_head = data;
    size_t *write_head = slice_get_ptr(slice, index);

    while (widths_left--)
        *write_head++ = *read_head++;
}

void slice_foreach(slice *slice, void (*fn)(void *)) {
    slice_index size = slice_size(slice);
    slice_index index;

    for (index = 0; index != size; ++index)
        fn(slice->begin + index * slice->width);
}
