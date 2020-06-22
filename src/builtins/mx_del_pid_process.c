#include "ush.h"

void mx_del_pid_process(t_ush *ush, int pid) {
    t_list *tmp = ush->processes;
    t_list *tmp2 = ush->processes;

    if (ush->processes) {
        if (((t_process*)tmp->data)->pid == pid) {
            mx_del_top_process(ush);
            return;
        }
        while (tmp->next) {
            if (((t_process*)tmp->next->data)->pid == pid) {
                tmp2 = tmp->next;
                tmp->next = tmp->next->next;
                mx_del_strarr(&((t_process*)tmp2->data)->name);
                free(tmp2->data);
                free(tmp2);
                return;
            }
            tmp = tmp->next;
        }
    }
}
