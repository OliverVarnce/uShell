#include "ush.h"

static int get_index(t_processes *process) {
    t_processes *tmp = process;
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

static bool is_exist(t_processes *process, pid_t pid) {
    t_processes *tmp = process;

    while (tmp) {
        if (process->pid == pid)
            return true;
        tmp = tmp->next;
    }
    return false;
}

int mx_add_process(t_processes **processes, pid_t pid, char **name) {
    int max_index = get_index(*processes);
    t_processes *pr = 0;

    if (is_exist(*processes, pid))
        return -1;
    pr = (t_processes*)malloc(sizeof(t_processes));
    pr->index = max_index + 1;
    pr->pid = pid;
    pr->name = mx_dupstrarr(name);
    mx_push_front_proc(processes, pr);
    return max_index + 1;
}
