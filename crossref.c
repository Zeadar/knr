#include "string_array.c"
#include "libkalle.c"
#include "types.h"
#include "slice.c"
#include <ctype.h>
#include <stdio.h>
#include <string.h>

#define BUFSIZE 1024

struct node {
    str_index word_index;
    str_index ref_index;
    slice_index left;
    slice_index right;
    u64 count;
} typedef node;

sarray stra;
slice nodes;

void addbranch(slice_index, char *, char *);
void printtree(slice_index);

int main() {
    stra = sarray_create();
    nodes = slice_new(struct node);

    char line_buf[BUFSIZE];
    char word_buf[BUFSIZE];
    char refe_buf[BUFSIZE];
    char *line_head, *word_head;
    int line_nr, word_pos, word_len, line_len;

    for (line_nr = 1; (line_len = readline(line_buf, BUFSIZE)); ++line_nr) {
        line_head = line_buf;

        while (*line_head != '\0') {
            word_head = word_buf;

            while (!isalnum(*line_head) && *line_head != '\0')
                ++line_head;

            word_pos = line_head - line_buf;

            for (word_len = 0;
                 isalnum(*line_head) && word_len < BUFSIZE - 1; ++word_len)
                *word_head++ = *line_head++;

            *word_head = '\0';

            if (word_len) {     //Found word
                sprintf(refe_buf, "%d, %d; ", line_nr, word_pos);
                addbranch(0, word_buf, refe_buf);
            }
        }

    }

    printtree(0);

    printf("String array size: %lu, allocated: %lu\n", stra.head,
           stra.end);
    printf("slice size: %lu\n", slice_size(&nodes));

    slice_destroy(&nodes);
    sarray_destroy(&stra);

    return 0;
}

slice_index alloc_node(char *word, char *ref) {
    node *new_node = slice_allocate(&nodes);
    new_node->word_index = sarray_push(&stra, word);
    new_node->ref_index = sarray_push(&stra, ref);
    new_node->left = -1;
    new_node->right = -1;
    new_node->count = 1;
    return slice_find(&nodes, new_node);
}

void addbranch(slice_index si, char *word, char *ref) {
    node *nptr = slice_get_ptr(&nodes, si);

    if (!nptr) {
        alloc_node(word, ref);
        return;
    }

    char *word_from_node = sarray_get(&stra, nptr->word_index);
    s64 condition = strcmp(word, word_from_node);

    if (condition == 0) {
        char *old_ref = sarray_get(&stra, nptr->ref_index);
        char *ref_buf = malloc(strlen(old_ref) + strlen(ref) + 2);
        strcpy(ref_buf, old_ref);
        strcat(ref_buf, ref);
        nptr->ref_index = sarray_push(&stra, ref_buf);
        nptr->count += 1;
        free(ref_buf);
    } else if (condition < 0) { // goes left
        if (nptr->left < 0)
            nptr->left = alloc_node(word, ref);
        else
            addbranch(nptr->left, word, ref);
    } else {                    // goes right
        if (nptr->right < 0)
            nptr->right = alloc_node(word, ref);
        else
            addbranch(nptr->right, word, ref);
    }
}

void printtree(slice_index index) {
    node *nptr = slice_get_ptr(&nodes, index);

    if (nptr) {
        printf("%.3lu %s\n", nptr->count,
               sarray_get(&stra, nptr->word_index));
        printf("\t%s\n", sarray_get(&stra, nptr->ref_index));
        // printf
        //     ("ref_index %lu\nword_index %lu\nleft %ld\nright %ld\ncount %lu\n\n",
        //      nptr->ref_index, nptr->word_index, nptr->left, nptr->right,
        //      nptr->count);
        printtree(nptr->left);
        printtree(nptr->right);
    }
}
