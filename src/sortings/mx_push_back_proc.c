#include "ush.h"

void mx_push_back_proc(t_processes **list, void *data) {
    if (*list == NULL) {
        *list = mx_create_proc_node(data);
        return;
    }

    t_processes *walker = *list;
    for (; walker->next != NULL; walker = walker->next);
    walker->next = mx_create_proc_node(data);
}
