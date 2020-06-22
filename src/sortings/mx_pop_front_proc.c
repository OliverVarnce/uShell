#include "ush.h"

void mx_pop_front_proc(t_processes **head) {
    if (head == NULL || *head == NULL)
        return;

    t_processes *tmp = *head;
    *head = tmp->next;
    free(tmp);
}
