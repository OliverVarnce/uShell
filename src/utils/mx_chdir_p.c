#include "ush.h"

int mx_chdir_p(char *path, t_ush *ush, char flags) {
    if (path == 0)
        return 0;
    if (chdir(path) == -1) {
        if ((flags & 1) == 0)
            fprintf(stderr, "cd: %s: %s\n", strerror(errno), path);
        return 1;
    }
    free(ush->old_pwd);
    ush->old_pwd = ush->pwd;
    ush->pwd = getcwd(NULL, 0);
    free(ush->pwd_l);
    ush->pwd_l = getcwd(NULL, 0);
    free(ush->pwd_p);
    ush->pwd_p = getcwd(NULL, 0);
    free(ush->pwd);
    ush->pwd = getcwd(NULL, 0);
    return 0;
}
