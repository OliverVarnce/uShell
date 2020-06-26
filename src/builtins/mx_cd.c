#include "ush.h"

static int flags_in_str(char *s) {
    int i = 0;
    int flag = 0;

    if (s[i + 1] == '\0') 
        return 4;
    while(s[++i]) {
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

static int use_flags(char **av, int *i) {
    int flag = 0;

    while(av[++(*i)]) {
        if (mx_strcmp(av[(*i)], "--") == 0) {
            (*i)++;
            return flag;
        }
        if (av[(*i)][0] != '-')
            return flag;
        int curr = flags_in_str(av[*i]);
        if (curr == -1)
            return 0;
        flag |= curr;
    }
    i--;
    return flag;
}

static void pwd_to_old(t_ush *ush) {
    char **buf = (char **) malloc(4 * sizeof (char *));

    buf[0] = mx_strdup("cd");
    buf[1] = mx_strjoin("PWD=", ush->pwd);
    buf[2] = mx_strjoin("OLDPWD=", ush->old_pwd);
    buf[3] = 0;
    mx_export(buf, &ush->var_tree, ush);
    mx_del_strarr(&buf);
}

int mx_cd(char **av, t_ush *ush) {
    int i = 0;
    int flags = use_flags(av, &i);
    char *path = (flags & 4) ? ush->old_pwd : (av[i] ? av[i]
        : mx_return_var2("HOME", &(ush->var_tree)));
    int status  = 0;

    if (mx_is_link(path) && (flags & 1) && (flags & 2) == 0) {
        fprintf(stderr, "cd: not a directory: %s\n", av[i]);
        return 1;
    }
    if (flags & 2)
        status = mx_chdir_p(path, ush, flags);
    else
        status = mx_chdir_l(path, ush, flags);
    if (status == 0)
        pwd_to_old(ush);
    ush->last_status = status;
    return status;
}

