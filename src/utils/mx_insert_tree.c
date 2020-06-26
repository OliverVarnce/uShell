#include "ush.h"

static void mx_min(t_tnode **root, t_tnode *new, int (*cmp)(void*, void*),
                       void (*free_)(void *)) {
    if ((*root)->left == 0) {
        (*root)->left = new;
        new->parent = *root;
    }
    else
        mx_insert_tree(&((*root)->left), new, cmp, free_);
}

static void not_min(t_tnode **root, t_tnode *new, int (*cmp)(void*, void*),
                       void (*free_)(void *)) {
    if ((*root)->right == 0) {
        (*root)->right = new;
        new->parent = *root;
    }
    else
        mx_insert_tree(&((*root)->right), new, cmp, free_);
}

void mx_insert_tree(t_tnode **root, t_tnode *new, int (*cmp)(void*, void*),
                    void (*free_)(void *)) {
    if (*root == 0) {
        *root = new;
        return;
    }
    if (cmp((*root)->data, new->data) > 0) // new lesser
        mx_min(root, new, cmp, free_);
    else if(cmp((*root)->data, new->data) < 0)
        not_min(root, new, cmp, free_);
    else { // equal
        free_((*root)->data);
        (*root)->data = new->data;
        free(new);
    }
}
