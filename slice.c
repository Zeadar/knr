#pragma once

#include <stddef.h>
#include <stdlib.h>
#include "types.h"
#define STEP 4096
#define slice_new(data_t) slice_create(sizeof(data_t))
#define slice_get(data_t, slice, index) *(data_t *)slice_get_ptr(slice, index)

typedef struct slice {
    u8 *begin;
    u8 *head;
    u8 *end;
    u64 width;
} slice;

typedef s64 slice_index;

slice slice_create(u64 width) {
    u64 init_size = STEP + (width / STEP) * STEP;

    struct slice slice;
    slice.begin = malloc(init_size);
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

u64 slice_size(const slice *slice) {
    return (slice->head - slice->begin) / slice->width;
}

void slice_check_grow(slice *slice) {
    if (slice->head + slice->width < slice->end)
        return;

    u64 bytes_used = slice->head - slice->begin;
    u64 bytes_grow =
        slice->end - slice->begin + STEP + (slice->width / STEP) * STEP;

    slice->begin = realloc(slice->begin, bytes_grow);
    slice->head = slice->begin + bytes_used;
    slice->end = slice->begin + bytes_grow;
}

slice_index slice_find(slice *slice, void *ptr) {
    u8 *find_me = ptr;

    if (find_me < slice->begin || find_me >= slice->head)
        return -1;

    return (find_me - slice->begin) / slice->width;
}

void *slice_allocate(slice *slice) {
    slice_check_grow(slice);

    slice->head += slice->width;
    return slice->head - slice->width;
}

slice_index slice_push(slice *slice, void *data) {
    slice_check_grow(slice);

    u64 byte_width = slice->width;
    while (byte_width--)
        *slice->head++ = *(u8 *) data++;

    return (slice->head - slice->begin) / slice->width;
}

void slice_remove(slice *slice, u64 index) {
    if (index >= slice_size(slice))
        return;

    u8 *here = slice->begin + index * slice->width;
    u8 *last = slice->head - slice->width;
    u64 byte_with = slice->width;

    while (byte_with--)
        *here++ = *last++;

    slice->head = slice->head - slice->width;
}

void slice_serial_remove(slice *slice, u64 index) {
    u64 item_size = slice_size(slice);

    if (index >= item_size)
        return;

    if (index != item_size - 1) {
        u8 *here = slice->begin + index * slice->width;
        u8 *next = slice->begin + (index + 1) * slice->width;

        while (next != slice->head)
            *here++ = *next++;
    }

    slice->head = slice->head - slice->width;
}

void *slice_get_ptr(const slice *slice, slice_index index) {
    if (index >= (slice_index) slice_size(slice) || index < 0)
        return 0;

    return slice->begin + index * slice->width;
}
