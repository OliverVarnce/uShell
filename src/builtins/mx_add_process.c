#include "ush.h"

static int curr_index(t_process *process) {
    t_process *tmp = process;
    int lim = 0;

    if (tmp == 0)
        return 0;
    lim = tmp->index;
    while (tmp) {
        if (lim < tmp->index) {
            lim = tmp->index;
        }
        tmp = tmp->next;
    }
    return lim;
}

static bool my_exist(t_process *process, pid_t pid) {
    t_process *tmp = process;

    while (tmp) {
        if (process->pid == pid)
            return true;
        tmp = tmp->next;
    }
    return false;
}

void mx_push_front_proc(t_process **list, t_process *new_head) {
    new_head->next = *list;
    *list = new_head;
}

int mx_add_process(t_process **processes, pid_t pid, char **name) {
    int index2 = curr_index(*processes);
    t_process *pr = 0;

    if (my_exist(*processes, pid))
        return -1;
    pr = (t_process*)malloc(sizeof(t_process));
    pr->index = index2 + 1;
    pr->pid = pid;
    pr->name = mx_dupstrarr(name);
    pr->next = NULL;
    mx_push_front_proc(processes, pr);
    return index2 + 1;
}
