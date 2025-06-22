#pragma once

#include <stddef.h>
#include <stdlib.h>
#include "slice.c"
#include "types.h"
#include "string_array.c"
#define GROWSIZE 4096
#define hashy_new(data_t) hashy_create(sizeof(data_t))

typedef struct hash_map {
    Sarray keys;
    Slice value_data;
    slice_index *map;
    slice_index size;
    slice_index used;
} Map;

u64 fnv1a(const char *str) {
    u64 hash = 14695981039346656037UL;
    while (*str) {
        hash ^= (u8) * str++;
        hash *= 1099511628211UL;
    }
    return hash;
}

void hashy_check_grow(Map *map) {
    if (map->used < map->size / 2)
        return;

    map->size *= 2;
    slice_index *new_map = malloc(map->size * sizeof(slice_index));

    free(map->map);
    map->map = new_map;

    for (slice_index i = 0; i != map->size; ++i)
        new_map[i] = -1;

    for (slice_index i = 0; i != map->used; ++i) {
        u64 hash_index =
            fnv1a(sarray_get(&map->keys, i)) % (map->size - 1);

        while (new_map[hash_index] != -1)
            hash_index = (hash_index + 1) % (map->size - 1);

        new_map[hash_index] = i;
    }

}

Map hashy_create(size_t byte_width) {
    size_t init_size = GROWSIZE * sizeof(slice_index);
    slice_index slots = init_size / sizeof(slice_index);
    Map map = {
        .keys = sarray_create(),
        .value_data = slice_create(byte_width),
        .map = malloc(init_size),
        .size = slots,
        .used = 0,
    };

    for (slice_index i = 0; i != slots; ++i)
        map.map[i] = -1;

    return map;
}

void hashy_install(Map *map, const char *key, const void *data) {
    hashy_check_grow(map);

    u64 hash_index = fnv1a(key) % (map->size - 1);

    while (map->map[hash_index] != -1) {
        if (strcmp(key, sarray_get(&map->keys, map->map[hash_index])) == 0) {
            slice_replace(&map->value_data, map->map[hash_index], data);
            return;
        }

        hash_index = (hash_index + 1) % (map->size - 1);
    }

    sarray_push(&map->keys, key);
    slice_push(&map->value_data, data);

    map->map[hash_index] = map->used++;
}

void *hashy_get(const Map *map, const char *key) {
    u64 hash_index = fnv1a(key) % (map->size - 1);
    char *current_key;

    while (map->map[hash_index] != -1) {
        current_key = sarray_get(&map->keys, map->map[hash_index]);
        if (strcmp(key, current_key) == 0)
            return slice_get_ptr(&map->value_data, map->map[hash_index]);

        hash_index = (hash_index + 1) % (map->size - 1);
    }

    return 0;
}

void hashy_foreach(const Map *map, void (fn) (char *key, void *value)) {
    char *key;
    void *value;

    for (slice_index i = 0; i != map->used; ++i) {
        key = sarray_get(&map->keys, i);
        value = slice_get_ptr(&map->value_data, i);
        fn(key, value);
    }
}

void hashy_destroy(Map *map) {
    sarray_destroy(&map->keys);
    slice_destroy(&map->value_data);
    free(map->map);
    map->map = 0;
    map->size = 0;
    map->used = 0;
}
