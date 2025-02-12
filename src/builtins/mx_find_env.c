#include "ush.h"

static void false_env(t_var *var) {
    while (var) {
        var->flag = 0;
        var = var->next;
    }
}

static bool get_path(char **path, int *i, char **av) {
    if (*path)
        free(*path);
    *path = mx_find_env_path(av[*i], av[*i + 1], i);
    if (*path == NULL) {
        mx_printerr_env(av[*i - 1], 0);
        return 1;
    }
    return 0;
}

bool mx_find_env(char **av, char **path, t_var *var, int *i) {
    if (strcmp(av[*i], "=") == 0 && mx_printerr_env(NULL, 2))
        return 1;
    else if (mx_reg(av[*i], MX_REG_ERR)) {
        mx_printerr_env(av[*i], 1);
        return 1;
    }
    else if (mx_reg(av[*i], MX_REG_P)) {
        if (get_path(path, i, av))
            return 1;
    }
    else if (mx_reg(av[*i], MX_REG_U))
        if (mx_del_variable_env(av[*i], av[*i + 1], var, i)) {
            mx_printerr_env(av[*i - 1], 0);
            return 1;
        }
    if (mx_reg(av[*i - 1], MX_REG_I) || mx_reg(av[*i], MX_REG_I))
        false_env(var);
    return 0;
}
