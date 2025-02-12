#include "ush.h"

static char *read_bqute(int des, int des2) {
    char *str = 0;
    char *tmp = malloc(1025 * sizeof(char));
    ssize_t check;
    ssize_t check2 = 0;

    close(des2);
    for (; (check = read(des, tmp, 1024)) != 0;) {
        str = realloc(str, check2 + check + 1);
        mx_memcpy(&str[check2], tmp, check);
        check2 += check;
    }
    if (check2 > 1)
        str[check2 - 1] = 0;
    close(des);
    free(tmp);
    return str;
}

static char *read_to_delim(int des, int des2) {
    char *str = read_bqute(des, des2);
    int i = -1;

    for (; str && str[++i] != 0;)
        if (str[i] == '\n')
            str[i] = '\x0d';
    if (str) {
        i = strlen(str);
        if (str[i - 1] == '\x0d')
            str[i - 1] = 0;
    }
    return str;
}

static void child(t_ush *processes, int des[2], char **str) {
    close(des[0]);
    dup2(des[1], 1);
    mx_parsing(*str, processes);
    if (processes->last_return == 130 || !(processes->if_ctrl_c))
        exit(130);
    exit(0);
}

static void parent(t_ush *processes, char **str) {
    int status;
    int check;

    wait(&status);
    check = MX_EXSTATUS(status);
    mx_strdel(str);
    if (check == 130) {
        processes->if_ctrl_c = 0;
    }
}

char *mx_bquote_str(char **str, t_ush *processes) {
    int des[2] = {0, 0};
    pid_t pid;
    char *test = 0;

    pipe(des);
    pid = fork();
    if (pid == 0)
        child(processes, des, str);
    else if (pid == -1) {
        mx_printerr(strerror(errno));
        exit(1);
    }
    else
        test = read_to_delim(des[0], des[1]);
    parent(processes, str);
    if (!processes->if_ctrl_c) {
        mx_strdel(&test);
        return 0;
    }
    return test;
}
