#include "ush.h"

static void emp () {
}

static char* mx_get_link_path(char *path) {
    char *link_path = malloc(1024);
    int len = 0;

    if ((len = readlink(path, link_path, sizeof(link_path) - 1)) == -1) {
        return 0;
    }
    link_path[len] = 0;
    return link_path;
}

static char *get_pwd() {
    char *pwd = mx_strdup(getenv("PWD"));
    char *cwd = getcwd(NULL, 0);
    char *link_path = 0;

    if (pwd == 0)
        return cwd;
    if (mx_is_link(pwd)) {
        link_path = mx_get_link_path(pwd);
        pwd = mx_del_last_var(pwd);
        pwd = mx_str_merge(mx_str_concatenation(pwd, "/"), link_path);
        if (mx_strcmp(pwd, cwd) == 0) {
            free(cwd);
            free(pwd);
            return mx_strdup(getenv("PWD"));
        }
    }
    free(pwd);
    return cwd;
}


void mx_ush_init(t_ush **ush, char **envp) {
    t_ush *new_info = (t_ush*) malloc(sizeof(t_ush));

    new_info->env = envp;
    new_info->processes = 0; // empty
    new_info->is_exit = false;
    new_info->exit_status = 0;
    new_info->pwd = get_pwd();
    new_info->pwd_p = getcwd(NULL, 0);
    new_info->pwd_l = mx_strdup(new_info->pwd);
    new_info->old_pwd = get_pwd();
    new_info->last_return = 0;
    *ush = new_info;
    mx_launch_ush(&(new_info->var_tree), envp);
    signal(SIGSEGV, NULL);
    signal(SIGINT, emp);
    signal(SIGTSTP, emp);
}
