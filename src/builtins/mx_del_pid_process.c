#include "ush.h"

void mx_del_pid_process(t_ush *ush, int pid) {
    t_process *tmp = ush->processes;
    t_process *tmp2 = ush->processes;

    if (ush->processes) {
        if (tmp->pid == pid) {
            mx_del_top_process(ush);
            return;
        }
        while (tmp->next) {
            if (tmp->next->pid == pid) {
                tmp2 = tmp->next;
                tmp->next = tmp->next->next;
                mx_del_strarr(&(tmp2->name));
                free(tmp2);
                return;
            }
            tmp = tmp->next;
        }
    }
}
