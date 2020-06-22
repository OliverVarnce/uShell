#include "ush.h"

static void check_status(char **argv, int status, t_ush *ush, pid_t pr) {
    char **mas_name = 0;

    if (MX_WIFSIG(status)) {
        if (MX_WTERMSIG(status) == SIGINT) {
            mx_del_pid_process(ush, pr);
            ush->last_return = 130;
        }
    }
    else {
        mx_add_process(&(ush->processes), pr, argv);
        mas_name = mx_get_name(ush, pr);
        mx_print_susp(mas_name);
    }
}

void mx_wait_process(t_ush *ush, char **argv) {
    int status = 0;
    pid_t pr = 0;

    pr = waitpid(-1, &status, WUNTRACED); 
    if (!MX_WIFEXIT(status)) {
        check_status(argv, status, ush, pr);
    }
    else {
        mx_del_pid_process(ush, pr);
        ush->last_return = MX_EXSTATUS(status);
    }
}
