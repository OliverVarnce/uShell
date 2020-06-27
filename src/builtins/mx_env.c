#include "ush.h"

static void name_and_val(t_var *var, char **av, int *i) {
    var->name = strndup(av[*i], mx_get_char_index(av[*i], '='));
    var->value = mx_strdup(av[*i]);
    var->flag = 1;
    var->next = NULL;
}

static void push_back(t_var *var, char *s) {
    char *name = strndup(s, mx_get_char_index(s, '='));

    while (var->next) {
        if (strcmp(var->name, name) == 0) {
            free(var->value);
            var->value = strdup(s);
            free(name);
            var->flag = 1;
            return;
        }
        var = var->next;
    }
    var->next = malloc(sizeof(t_var));
    var = var->next;
    var->value = strdup(s);
    var->flag = 1;
    var->name = name;
    var->next = NULL;
}

static bool print_env(t_var *var, char **av, int *i) {
    if (av[*i] == NULL) {
        mx_print_env(var);
        return 1;
    }
    for (; av[*i]; (*i)++) {
        if (mx_reg(av[*i], MX_REG_VER)) {
            if (var->value == NULL)
                name_and_val(var, av, i);
            else 
                push_back(var, av[*i]);
        }
        else
            break;
    }
    if (av[*i] == NULL) {
        mx_print_env(var);
        return 1;
    }
    return 0;
}

void mx_env(char **av, t_ush *ush) {
    t_var *var = mx_var_tree_to_var(ush->var_tree);
    char *path = NULL;
    int i = 0;

    for (i = 1; av[i] != NULL; i++) {
        if (mx_reg(av[i], MX_REG_VER) || mx_reg(av[i], MX_REG_PROG))
            break;
        if (mx_find_env(av, &path, var, &i)) {
            mx_clear_path(var, path);
            ush->last_return = 1;
            return;
        }
    }
    if (print_env(var, av, &i)) {
        mx_clear_path(var, path);
        return;
    }
    mx_exec_env_pr(path, mx_call_env(av, i), mx_env_to_ush(var), ush);
    mx_clear_path(var, path);
}
