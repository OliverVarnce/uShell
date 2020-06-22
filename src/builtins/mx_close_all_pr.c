#include "ush.h"

void mx_close_all_pr(t_ush *ush) {
    t_list *tmp = ush->processes;

    while (tmp) {
        if (kill(((t_processes*)tmp->data)->pid, SIGKILL) == 0)
            printf("Process [%d] killed\n", ((t_processes*)tmp->data)->pid);
        tmp = tmp->next;
    }
}
