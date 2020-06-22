#include "ush.h"

void mx_push_front_proc(t_processes **list, void *data) {
    t_processes *new_node = mx_create_proc_node(data);
    new_node->next = *list;
    *list = new_node;
}
