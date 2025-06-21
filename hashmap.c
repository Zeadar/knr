#include "types.h"
#include "libkalle.c"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BUFSIZE 512
#define HASHSIZE (BUFSIZE - 1)

struct nlist {
    struct nlist *next;
    u64 count;
    char *name;
};

u64 hash(const char *);
void insert(struct nlist **, const char *, const u64);
void print(const struct nlist *);

int main() {
    struct nlist *hashlist[BUFSIZE] = { 0 };
    int word_size;
    char buffer[BUFSIZE];

    while ((word_size = getword(buffer, BUFSIZE))) {
        u64 h = hash(buffer) % HASHSIZE;
        // printf("%.2d %.4lu %s\n", word_size, h, buffer);

        insert(&hashlist[h], buffer, word_size + 1);
    }

    for (u64 i = 0; i != BUFSIZE; ++i)
        if (hashlist[i]) {
            printf("hash: %lu\n", i);
            print(hashlist[i]);
        }


    return 0;
}

u64 hash(const char *str) {     //djb2
    u64 hashvalue = 5381;
    int c;
    while ((c = *str++) != '\0')
        hashvalue = ((hashvalue << 5) + hashvalue) + c; // hash * 33 + c
    return hashvalue;
}

void insert(struct nlist **next, const char *name, const u64 name_size) {
    struct nlist *candidate = *next;

    if (candidate) {
        if (strcmp(candidate->name, name) == 0)
            candidate->count += 1;
        else
            insert(&candidate->next, name, name_size);
    } else {
        candidate = malloc(sizeof(struct nlist));
        candidate->next = 0;
        candidate->count = 1;
        candidate->name = malloc(name_size);
        strcpy(candidate->name, name);
        *next = candidate;
    }
}

void print(const struct nlist *next) {
    printf("%.4lu %s", next->count, next->name);

    if (next->next) {
        printf("\n->\t");
        print(next->next);
    } else
        printf("\n");
}
