#include "ush.h"

t_processes *mx_create_proc_node(void *data) {
    t_processes *node = (t_processes *)malloc(sizeof(t_processes));

    if (!node)
        return NULL;

    node->data = data;
    node->next = NULL;

    return node;
}
