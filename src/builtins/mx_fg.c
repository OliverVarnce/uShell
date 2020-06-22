#include "ush.h"

static t_process* get_process(int n, char *str, t_ush *ush) {
    t_list *tmp = ush->processes;

    if (n != -1) {
        while (tmp) {
            if (((t_process*)tmp->data)->index == n)
                return ((t_process*)tmp->data);
            tmp = tmp->next;
        }
        fprintf(stderr, "fg: job not found: %s\n", str);
    }
    else {
        while (tmp) {
            if (mx_is_str_starts(((t_process*)tmp->data)->name[0], str))
                return ((t_process*)tmp->data);
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
    t_process *pr = (t_process*)ush->processes->data;
    int i = 0;

    if (argv[1] == 0) {
        kill(pr->pid, SIGCONT);
        return 0;
    }
    i = (argv[1][0] == '%') ? 1 : 0;
    if (mx_is_number_fg(argv[1])) {
            pr = get_process(atoi(&argv[1][i]), argv[1], ush);
    }
    else {
        pr = get_process(-1, &argv[1][i], ush);
    }
    if (pr == 0) {
        ush->exit_status = 1;
        return 1;
    }
    mx_print_cont(pr->name, pr->index);
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
            mx_print_susp(str);
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
