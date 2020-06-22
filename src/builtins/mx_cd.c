#include "ush.h"

static int flag_from_cmd(char *s) {
    int i = 0;
    int flag = 0;

    if (s[i + 1] == '\0')
        return 4;
    while(s[++i])  {
        if (s[i] == 's')
            flag |= 1;
        else if (s[i] == 'P')
            flag |= 2;
        else {
            return -1;
        }
    }
    return flag;
}

static int check_flag(char **av, int *i) {
    int flags = 0;
//    int actual;

    while(av[++(*i)]) {
        if (mx_strcmp(av[(*i)], "--") == 0) {
            (*i)++;
            return flags;
        }
        if (av[(*i)][0] != '-')
            return flags;
        int actual = flag_from_cmd(av[*i]);
        if (actual == -1)
            return 0;
        flags |= actual;
    }
    i--;
    return flags;
}

static void pwd_to_old(t_ush *ush) {
    char **tmp = (char **) malloc(4 * sizeof (char *));

    tmp[0] = mx_strdup("cd");
    tmp[1] = mx_strjoin("PWD=", ush->pwd);
    tmp[2] = mx_strjoin("OLDPWD=", ush->old_pwd);
    tmp[3] = 0;
    mx_export(tmp, &ush->var_tree, ush);
    mx_del_strarr(&tmp);
}

int mx_cd(char **av, t_ush *ush) {
    int i = 0;
    int flag = check_flag(av, &i);
    char *path = (flag & 4) ? ush->old_pwd : (av[i] ? av[i]
        : mx_return_value2("HOME", &(ush->var_tree)));
    int status = 0;

    if (mx_is_link(path) && (flag & 1) && (flag & 2) == 0) {
        fprintf(stderr, "cd: not a directory: %s\n", av[i]);
        return 1;
    }
    if (flag & 2)
        status = mx_chdir_p(path, ush, flag);
    else
        status = mx_chdir_l(path, ush, flag);
    if (status == 0)
        pwd_to_old(ush);
    ush->last_status = status;
    return status;
}

