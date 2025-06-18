#include "string_array.c"
#include "libkalle.c"
#include "types.h"
#include "slice.c"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFSIZE 1024

typedef struct node {
    str_index word_index;
    slice_index ref_index;
    slice_index left;
    slice_index right;
    u64 count;
} node;

sarray stra;
slice nodes;
slice refs;

void addbranch(slice_index, char *, char *);
void printtree(slice_index);
void freedom(void *);
int compare_counts(const void *, const void *);

int main() {
    stra = sarray_create();
    nodes = slice_new(struct node);
    refs = slice_new(char *);

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

            for (word_len = 0; (isalpha(*line_head) || *line_head == '_')
                 && word_len < BUFSIZE - 1; ++word_len)
                *word_head++ = tolower(*line_head++);

            *word_head = '\0';

            if (word_len > 1) { //Found word and is more than one letter
                sprintf(refe_buf, "%d, %d; ", line_nr, word_pos);
                addbranch(0, word_buf, refe_buf);
            }
        }

    }

    // printtree(0);

    // printf("String array size: %lu, allocated: %lu\n", stra.head,
    //        stra.end);
    // printf("nodes size: %lu\n", slice_size(&nodes));

    slice to_sort = slice_new(node *);

    {
        slice_index i = 0;
        node *nptr;
        for (;;) {
            nptr = slice_get_ptr(&nodes, i++);
            if (!nptr)
                break;

            slice_push(&to_sort, &nptr);
        }
    }

    slice_qsort(&nodes, compare_counts);

    {
        slice_index i = 0;
        node *nptr;
        node **nptrptr;
        for (;;) {
            nptrptr = slice_get_ptr(&to_sort, i++);
            if (!nptrptr)
                break;

            nptr = *nptrptr;

            printf("%.4lu %s\n", nptr->count,
                   sarray_get(&stra, nptr->word_index));
        }
    }

    slice_foreach(&refs, freedom);
    slice_destroy(&refs);
    slice_destroy(&nodes);
    slice_destroy(&to_sort);
    sarray_destroy(&stra);

    return 0;
}

slice_index alloc_node(char *word, char *ref) {
    node *new_node = slice_allocate(&nodes);
    new_node->word_index = sarray_push(&stra, word);

    char *new_ref = malloc(strlen(ref) + 1);
    strcpy(new_ref, ref);
    new_node->ref_index = slice_push(&refs, &new_ref);

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
        char *ref_ptr = *(char **) slice_get_ptr(&refs, nptr->ref_index);
        ref_ptr = realloc(ref_ptr, strlen(ref_ptr) + strlen(ref) + 1);
        strcat(ref_ptr, ref);
        slice_replace(&refs, nptr->ref_index, &ref_ptr);

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

void freedom(void *help_me) {
    char *free_me = *(char **) help_me;
    free(free_me);
}

void printtree(slice_index index) {
    node *nptr = slice_get_ptr(&nodes, index);

    if (nptr) {
        printf("%.3lu %s\n", nptr->count,
               sarray_get(&stra, nptr->word_index));
        printf("\t%s\n", *(char **) slice_get_ptr(&refs, nptr->ref_index));

        // printf
        //     ("word: %s\nref_index %lu\nword_index %lu\nleft %ld\nright %ld\ncount %lu\n\n",
        //      sarray_get(&stra, nptr->word_index), nptr->ref_index,
        //      nptr->word_index, nptr->left, nptr->right, nptr->count);
        printtree(nptr->left);
        printtree(nptr->right);
    }
}

int compare_counts(const void *a, const void *b) {
    const node *sa = a;
    const node *sb = b;

    return sb->count - sa->count;
}
