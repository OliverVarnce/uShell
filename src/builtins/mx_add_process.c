#include "ush.h"

static int get_index(t_process *process) {
    t_process *tmp = process;
    int max = 0;

    if (tmp == 0)
        return 0;
    max = tmp->index;
    while (tmp) {
        if (max < tmp->index) {
            max = tmp->index;
        }
        tmp = tmp->next;
    }
    return max;
}

static bool is_exist(t_process *process, pid_t pid) {
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
    int max_index = get_index(*processes);
    t_process *pr = 0;

    if (is_exist(*processes, pid))
        return -1;
    pr = (t_process*)malloc(sizeof(t_process));
    pr->index = max_index + 1;
    pr->pid = pid;
    pr->name = mx_dupstrarr(name);
    pr->next = NULL;
    mx_push_front_proc(processes, pr);
    return max_index + 1;
}
