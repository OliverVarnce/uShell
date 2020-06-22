#include "ush.h"

void mx_not_stdin_terminal(t_ush *ush, int argc, char *argv[]) {
    char *str = 0;
    char *temp = mx_strnew(1024);
    char *temp2 = 0;
    ssize_t check;
    int i = -1;

    ush->if_ctrl_c = 1;
    while ((check = read(0, temp, 1024)) != 0) {
        temp2 = mx_strndup(temp, check);
        str = mx_strjoin3(str, temp2);
    }
    free(temp);
    while (str && str[++i] != 0)
        if (str[i] == '\n')
            str[i] = ';';
    mx_parsing(str, ush);
    free(str);
    argv++;
    argc++;
}

int main(int argc, char *argv[], char **envp) {
    int str = 1;
    t_ush *ush = 0;

    mx_get_twidth();
    mx_ush_init(&ush, envp);
    if (isatty(0) == 0) 
        mx_not_stdin_terminal(ush, argc, argv);
    else
        mx_loop(str, ush);
    mx_ush_close(ush);
    system("leaks ush");
    return ush->exit_status;
}
