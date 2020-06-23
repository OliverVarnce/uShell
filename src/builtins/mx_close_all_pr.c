#include "ush.h"

void mx_close_all_pr(t_ush *ush) {
    t_process *tmp = ush->processes;

    while (tmp) {
        if (kill(tmp->pid, SIGKILL) == 0)
            printf("Process [%d] killed\n", tmp->pid);
        tmp = tmp->next;
    }
}
