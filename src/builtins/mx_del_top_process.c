#include "ush.h"

void mx_pop_front_proc(t_process **head) {
    t_process *now = NULL;

    if (head && *head) {
        now = (*head)->next;
        mx_del_strarr(&((*head)->name));
        free(*head);
        *head = now;
    }
}

void mx_del_top_process(t_ush *ush) {
    if (!ush->processes)
        return;
    mx_del_strarr(&(ush->processes->name));
    mx_pop_front_proc(&ush->processes);
}
