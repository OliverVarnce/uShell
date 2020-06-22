#include "ush.h"

char **mx_get_name(t_ush *ush, int numb) {
    t_processes *head_pr = ush->processes;

    while (head_pr) {
        if (head_pr->pid == numb) {
            return head_pr->name;
        }
        head_pr = head_pr->next;
    }
    return 0;
}
