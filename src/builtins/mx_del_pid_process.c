#include "ush.h"

void mx_del_pid_process(t_ush *ush, int pid) {
    t_processes *tmp = ush->processes;
    t_processes *newtmp = ush->processes;

    if (ush->processes) {
        if (tmp->pid == pid) {
            mx_del_top_process(ush);
            return;
        }
        while (tmp->next) {
            if (tmp->next->pid == pid) {
                newtmp = tmp->next;
                tmp->next = tmp->next->next;
                mx_del_strarr(&newtmp->name);
                mx_strdel(newtmp->data);
                free(newtmp);
                return;
            }
            tmp = tmp->next;
        }
    }
}
