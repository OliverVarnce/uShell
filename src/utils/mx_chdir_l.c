#include "ush.h"

static int get_rank(char *path) {
    int i = -1;
    int rank = 0;

    while(path[++i]) {
        if ((path[i] == '/') && (path[i + 1])) {
            rank++;
        }
    }
    return rank;
} 

static char *get_new_pwd(char *path, t_ush *ush) {
    char **tokens = mx_strsplit(path, '/');
    char *tmp_pwd = path[0] == '/' ? mx_strdup("/") : mx_strdup(ush->pwd_l);
    char *res = 0;

    for (int i = 0; tokens[i]; i++)
        if (mx_strcmp(tokens[i], "..") == 0) {
            if (get_rank(tmp_pwd) == 0)
                continue;
            tmp_pwd = mx_del_last_rank(tmp_pwd);
        }
        else 
            tmp_pwd = mx_add_one_rank(tmp_pwd, tokens[i]);
    if (tmp_pwd[0] != '/') {
        res = mx_strjoin("/", tmp_pwd);
        free(tmp_pwd);
    }
    else
        res = tmp_pwd;
    mx_del_strarr(&tokens);
    return res;
}

int mx_chdir_l(char *path, t_ush *ush, char flags) {
    char *new_pwd = 0;

    if (path == 0)
        return 0;
    new_pwd = get_new_pwd(path, ush);
    if (chdir(new_pwd) == -1) {
        if ((flags & 1) == 0)
        fprintf(stderr, "cd: %s: %s\n", strerror(errno), new_pwd);
        free(new_pwd);
        return 1;
    }
    free(ush->old_pwd);
    ush->old_pwd = ush->pwd;
    free(ush->pwd_l);
    ush->pwd_l = new_pwd;
    free(ush->pwd_p);
    ush->pwd_p = getcwd(NULL, 0);
    ush->pwd = mx_strdup(ush->pwd_l);
    return 0;
}
