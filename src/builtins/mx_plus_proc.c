#include "ush.h"

static int take_index(t_list *process) {
    t_list *tmp = process;
    int max = 0;

    if (tmp == 0)
        return 0;
    max = ((t_process*)tmp->data)->index;
    while (tmp) {
        if (max < ((t_process*)tmp->data)->index) {
            max = ((t_process*)tmp->data)->index;
        }
        tmp = tmp->next;
    }
    return max;
}

static bool is_exist(t_list *process, pid_t pid) {
    t_list *tmp = process;

    while (tmp) {
        if (((t_process*)process->data)->pid == pid)
            return true;
        tmp = tmp->next;
    }
    return false;
}

int mx_plus_proc(t_list **processes, pid_t pid, char **name) {
    int max_ind = take_index(*processes);
    t_process *proc = 0;

    if (is_exist(*processes, pid))
        return -1;
    proc = (t_process*)malloc(sizeof(t_process));
    proc->index = max_ind + 1;
    proc->pid = pid;
    proc->name = mx_dupstrarr(name);
    mx_push_front(processes, proc);
    return max_ind + 1;
}
