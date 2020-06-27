#include "ush.h"

static t_process* get_process(int n, char *s, t_ush *ush) {
    t_process *tmp = ush->processes;

    if (n != -1) {
        while (tmp) {
            if (tmp->index == n)
                return tmp;
            tmp = tmp->next;
        }
        fprintf(stderr, "fg: job not found: %s\n", s);
    }
    else {
        while (tmp) {
            if (mx_is_str_begin(tmp->name[0], s))
                return tmp;
            tmp = tmp->next;
        }
        fprintf(stderr, "fg: job not found: %s\n", s);
    }
    return 0;
}

/*return true if all elements - numbers*/
static bool fg_is_persent(char *s) {
    int i = -1;
    if (s[0] == '%')
        i++;
    while (s[++i]) {
        if (s[i] < 48 || s[i] > 57)
            return false;
    }
    return true;
}

static int fg_continue(char **av, t_ush *ush) {
    t_process *pr = ush->processes;
    int i = 0;

    if (av[1] == 0) {
        kill(pr->pid, SIGCONT);
        return 0;
    }
    i = (av[1][0] == '%') ? 1 : 0;
    if (fg_is_persent(av[1])) {
            pr = get_process(atoi(&av[1][i]), av[1], ush);
    }
    else {
        pr = get_process(-1, &av[1][i], ush);
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
            char **str = mx_find_name(ush, ch_pr);
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
