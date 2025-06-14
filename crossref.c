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

    char *line_head, *word_head;
    int line_nr, word_pos, word_len, line_len;

    char line_buf[BUFSIZE];
    char word_buf[BUFSIZE];
    char refe_buf[BUFSIZE];

    for (line_nr = 1; (line_len = readline(line_buf, BUFSIZE)); ++line_nr) {
        line_head = line_buf;

        while (*line_head != '\0') {
            word_head = word_buf;

            while (!isalpha(*line_head) && *line_head != '\0')
                ++line_head;

            word_pos = line_head - line_buf;

            for (word_len = 0;
                 isalpha(*line_head) && word_len < BUFSIZE - 1; ++word_len)
                *word_head++ = tolower(*line_head++);

            *word_head = '\0';

            if (word_len) {     //Found word
                sprintf(refe_buf, "%d, %d; ", line_nr, word_pos);
                addbranch(0, word_buf, refe_buf);
            }
        }

    }

    printtree(0);

    // s64 word_amount = slice_size(&nodes) - 1;
    // node *nptrs = malloc(word_amount * sizeof(node *));

    // for (node * nptr = nptrs; nptr - nptrs < word_amount; ++nptr)
    //     nptr = slice_get_ptr(&nodes, nptrs - nptr);

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
        str_index old_ref_index = nptr->ref_index;
        char *old_ref = sarray_get(&stra, old_ref_index);
        u64 bytes = strlen(old_ref) + strlen(ref) + 1;

        char *new_ref = sarray_allocate(&stra, bytes, &(nptr->ref_index));

        //refetch in case old_ref is obsolete
        old_ref = sarray_get(&stra, old_ref_index);
        strcpy(new_ref, old_ref);
        strcat(new_ref, ref);

        nptr->count += 1;
    } else if (condition < 0) { // goes left
        if (nptr->left < 0) {
            slice_index new_node_idx = alloc_node(word, ref);
            nptr = slice_get_ptr(&nodes, si);   // alloc_node might make the old nptr obsolete
            nptr->left = new_node_idx;
        } else {
            addbranch(nptr->left, word, ref);
        }
    } else {                    // goes right
        if (nptr->right < 0) {
            slice_index new_node_idx = alloc_node(word, ref);
            nptr = slice_get_ptr(&nodes, si);   // alloc_node might make the old nptr obsolete
            nptr->right = new_node_idx;
        } else {
            addbranch(nptr->right, word, ref);
        }
    }
}

void printtree(slice_index index) {
    node *nptr = slice_get_ptr(&nodes, index);

    if (nptr) {
        printf("%.3lu %s\n", nptr->count,
               sarray_get(&stra, nptr->word_index));
        printf("\t%s\n", sarray_get(&stra, nptr->ref_index));
        // printf
        //     ("word: %s\nref_index %lu\nword_index %lu\nleft %ld\nright %ld\ncount %lu\n\n",
        //      sarray_get(&stra, nptr->word_index), nptr->ref_index,
        //      nptr->word_index, nptr->left, nptr->right, nptr->count);
        printtree(nptr->left);
        printtree(nptr->right);
    }
}
