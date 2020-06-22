#include "ush.h"

static t_processes* get_processes(int n, char *str, t_ush *ush) {
    t_list *tmp = ush->processes;

    if (n != -1) {
        while (tmp) {
            if (((t_processes*)tmp->data)->index == n)
                return ((t_processes*)tmp->data);
            tmp = tmp->next;
        }
        fprintf(stderr, "fg: job not found: %s\n", str);
    }
    else {
        while (tmp) {
            if (mx_is_str_starts(((t_processes*)tmp->data)->name[0], str))
                return ((t_processes*)tmp->data);
            tmp = tmp->next;
        }
        fprintf(stderr, "fg: job not found: %s\n", str);
    }
    return 0;
}

/*return true if all elements - numbers*/
static bool mx_is_number_fg(char *str) {
    int i = -1;
    if (str[0] == '%')
        i++;
    while (str[++i]) {
        if (str[i] < 48 || str[i] > 57)
            return false;
    }
    return true;
}

static int fg_continue(char **argv, t_ush *ush) {
    t_processes *pr = (t_processes*)ush->processes->data;
    int i = 0;

    if (argv[1] == 0) {
        kill(pr->pid, SIGCONT);
        return 0;
    }
    i = (argv[1][0] == '%') ? 1 : 0;
    if (mx_is_number_fg(argv[1])) {
            pr = get_processes(atoi(&argv[1][i]), argv[1], ush);
    }
    else {
        pr = get_processes(-1, &argv[1][i], ush);
    }
    if (pr == 0) {
        ush->exit_status = 1;
        return 1;
    }
    mx_print_stat(pr->name, pr->index, 1);
    kill(pr->pid, SIGCONT);
    return 0;
}

static void fg_wait(int status, pid_t ch_pr, t_ush *ush) {
    if (MX_WIFSIG(status)) {
        if (MX_WTERMSIG(status) == SIGINT) {
            mx_del_pid_process(ush, ch_pr);
            ush->last_return = 130;
        }
        else {
            char **str = mx_get_name(ush, ch_pr);
            mx_print_stat(str, 0, 0);
        }
    }
}

void mx_fg(char **argv, t_ush *ush) {
    pid_t ch_pr = 0;
    int status = 0;

    if (ush->processes) {
        if (fg_continue(argv, ush) == 0) {
            ch_pr = waitpid(-1, &status, WUNTRACED);
            if (!MX_WIFEXIT(status))
                fg_wait(status, ch_pr, ush);
            else {
                mx_del_pid_process(ush, ch_pr);
                ush->last_return = MX_EXSTATUS(status);
            }
        }
    }
    else
        mx_printerr("fg: no current job\n");
}
