#include "ush.h"

char **mx_find_name(t_ush *ush, int numb) {
    t_process *head_pr = ush->processes;

    while (head_pr) {
        if (head_pr->pid == numb) {
            return head_pr->name;
        }
        head_pr = head_pr->next;
    }
    return 0;
}
