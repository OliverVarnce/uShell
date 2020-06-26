#include "ush.h"

static int find_flags(int *i, char **av) {
    int flag = 0;

    while(av[++(*i)])
        if (av[*i][0] == '-') {
            for(int j = 1; j < mx_strlen(av[*i]); j++)
                if (av[*i][j] == 'a')
                    flag |= 1;
                else if(av[*i][j] == 's')
                    flag |= 2;
                else {
                    mx_printerr("which: bad option: -");
                    write(2, &av[*i][j], 1);
                    write(2, "\n", 1);
                    return -1;
                }
        }
        else
            return flag;
    return flag;
}

static int mx_check_buildin(char *com, int flags, bool *finded) {
    if (mx_is_buildin(com)) {
        if ((flags & 2) == 2)
            return 1;
        printf("%s: shell built-in command\n", com);
        *finded = true;
        if ((flags & 1) == 0)
            return 1;
    }
    return 0;
}


static bool check_command(char *com, char **pathes, int flags) {
    char *fullname = 0;
    bool finded = false;

    if (mx_check_buildin(com, flags, &finded) == 1)
        return true;
    if (com[0] == '/') {
        if (mx_is_commad(mx_strdup(com), flags))
                return true;
    }
    else {
        for(int i = 0; pathes[i]; i++) {
            fullname = mx_strjoin_new(mx_strjoin(pathes[i], "/"), com);
            if (mx_is_commad(fullname, flags)) {
                if ((flags & 1) == 0)
                    return true;
                finded = true;
            }
        }
    }
    return finded;
}

static bool check_commands(char **commands, char** pathes, int start_index,
                           int flags) {
    int i = start_index - 1;
    bool finded = false;

    while(commands[++i] != 0) {
        finded = check_command(commands[i], pathes, flags);
        if ((finded == false) && ((flags & 2) == 2))
            return false;
        if (finded == false) 
            printf("%s not found\n", commands[i]);
        if (finded && ((flags & 1) == 0 || (flags & 2) == 2))
            return true;
    }
    return finded;
}

void mx_which(char **argv, t_ush *ush) {
    char *path = mx_return_var2("PATH", &(ush->var_tree));
    char **pathes = mx_strsplit(path, ':');
    int i_args = 0;
    int flags = find_flags(&i_args, argv);
    int finded = false;
    
    if (flags == -1) {
        mx_del_strarr(&pathes);
        ush->last_status = 1;
        return;
    }
    finded = check_commands(argv, pathes, i_args, flags);
    finded ? (ush->last_status = 0) : (ush->last_status = 1);
    mx_del_strarr(&pathes);
}
