#include "libkalle.c"
#include "slice.c"
#include "string_array.c"
#include <stdio.h>
#include <string.h>
#include "types.h"
#define MAXWORD 100

struct tnode {
    u64 word_index;
    u64 count;
    struct tnode *left;
    struct tnode *right;
};

slice tree_container;
sarray str_array;

struct tnode *addtree(struct tnode *, char *);
struct tnode *talloc(void);
void treeprint(struct tnode *);

int main() {
    tree_container = slice_new(struct tnode);
    str_array = sarray_create();

    struct tnode *root;
    char word[MAXWORD];

    root = 0;

    while (getword(word, MAXWORD) != EOF)
        if (isalpha(word[0]))
            root = addtree(root, word);

    treeprint(root);

    // printf("arena size %d\n", sarray_size(&str_arena));

    sarray_destroy(&str_array);
    slice_destroy(&tree_container);

    return 0;
}

struct tnode *addtree(struct tnode *p, char *w) {
    int cond;

    if (p == 0) {
        p = talloc();
        p->word_index = sarray_push(&str_array, w);
        p->count = 1;
        p->left = 0;
        p->right = 0;
    } else if ((cond = strcmp(w, str_array.ptr + p->word_index)) == 0)
        p->count++;
    else if (cond < 0)
        p->left = addtree(p->left, w);
    else
        p->right = addtree(p->right, w);

    return p;
}

struct tnode *talloc(void) {
    // This is awful.
    // Slice might realloc() and then the returned pointer will not be valid anymore.
    return slice_allocate(&tree_container);
}

void treeprint(struct tnode *p) {
    if (p != 0) {
        treeprint(p->left);
        printf("%4ld %s\n", p->count, str_array.ptr + p->word_index);
        treeprint(p->right);
    }
}
