#include "ush.h"

void mx_not_stdin_term(t_ush *ush, int argc, char **argv) {
    char *tmp = mx_strnew(1024);
    char *temp2 = 0;
    char *str = 0;
    int i = -1;
    ssize_t check;

    ush->if_ctrl_c = 1;
    while ((check = read(0, tmp, 1024)) != 0) {
        temp2 = mx_strndup(tmp, check);
        str = mx_strjoin3(str, temp2);
    }
    free(tmp);
    while (str && str[++i] != 0)
        if (str[i] == '\n')
            str[i] = ';';
    mx_parsing(str, ush);
    free(str);
    argv++;
    argc++;
}

static void mysetenv() {
    struct passwd *pw = getpwuid(getuid());
    char *pwd = getcwd(NULL, 0);

    setenv("HOME", pw->pw_dir, 0);
    setenv("LOGNAME", getlogin(), 0);
    setenv("PWD", pwd, 0);
    setenv("OLDPWD",pwd, 0);
    if (getenv("SHLVL") != NULL) {
        char *num = getenv("SHLVL");
        *num += 1;
        setenv("SHLVL", num, 1);
    }
    else
        setenv("SHLVL", "1", 0);
    setenv("_", "/usr/bin/env", 0);
    free(pwd);
}

int main(int argc, char **argv, char **envp) {
    int str = 1;
    t_ush *ush = 0;

    if (*envp == NULL)
        mysetenv();

    mx_get_twidth();
    mx_ush_init(&ush, envp);
    if (isatty(0) == 0) 
        mx_not_stdin_term(ush, argc, argv);
    else
        mx_loop(str, ush);
    mx_ush_close(ush);
    //system("leaks ush");
    return ush->exit_status;
}
