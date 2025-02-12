#include "ush.h"

static void shlvl_new(char **s) {
    int a = 0;
    char *tmp = 0;
    int i = 0;
    int neg = 1;

    if (s[0][0] == '-') {
        i++;
        neg = -1;
    }
    for (; i < mx_strlen(s[0]); i++)
        a = a * 10 + (s[0][i] - '0');
    a = a * neg;
    mx_strdel(s);
    tmp = mx_itoa(++a);
    *s = tmp;
}

static char *create_mem(char *str1, char **str2, char *str3, char **value) {
    char *mem = 0;

    if (mx_strcmp(str1, "SHLVL") == 0) {
        shlvl_new(str2);
        mx_strdel(value);
        *value = mx_strdup(*str2);
        mem = mx_strjoin("SHLVL=", *str2);
    }
    else if (mx_strcmp(str1, "PWD") == 0) {
        mx_strdel(str2);
        *str2 = getcwd(NULL, 0);
        mem = mx_strjoin("PWD=", *str2);
    }
    else if (mx_strcmp(str1, "OLDPWD") == 0) {
        mx_strdel(str2);
        *str2 = getcwd(NULL, 0);
        mem = mx_strjoin("OLDPWD=", *str2);
    }
    else
        mem = mx_strdup(str3);
    return mem;
}

static bool check_if_env_have(char *name, t_variable **var_tree) {
    t_variable *var_tree_check = *var_tree;

    while (var_tree_check) {
        if (mx_strcmp(var_tree_check->name, name) == 0)
            return false;
        else
            var_tree_check = var_tree_check->next;
    }
    return true;
}

static void check_env(t_variable **var_tree) {
    char *tmp = 0;

    if (check_if_env_have("PWD", var_tree)) {
        tmp = getcwd(NULL, 0);;
        mx_filling_env(var_tree, mx_strdup("PWD"),
                    tmp, mx_strjoin("PWD=", tmp));
    }
    if (check_if_env_have("OLDPWD", var_tree)) {
        tmp = getcwd(NULL, 0);
        mx_filling_env(var_tree, mx_strdup("OLDPWD"), tmp,
                    mx_strjoin("OLDPWD=", tmp));
    }
    if (check_if_env_have("SHLVL", var_tree)) {
        tmp = mx_strdup("1");
        mx_filling_env(var_tree, mx_strdup("SHLVL"), tmp,
                    mx_strjoin("SHLVL=", tmp));
    }
}

void mx_launch_ush(t_variable **var_tree, char **env) {
    int i = -1;
    char **envvar = 0;
    char *tmp = 0;
    t_variable *var = 0;

    for (; env[++i];) {
        var = (t_variable *)malloc(sizeof(t_variable));
        envvar = mx_strsplit(env[i], '=');
        var->name = envvar[0];
        var->value = mx_strdup(&env[i][mx_strlen(var->name) + 1]);
        tmp = create_mem(envvar[0], &envvar[1], env[i], &(var->value));
        var->is_env = true;
        var->mem = tmp;
        var->next = NULL;
        putenv(tmp);
        mx_push_back_res(var_tree, var);
        if (envvar) {
            mx_strdel(&envvar[1]);
            free(envvar);
        }

    }
    check_env(var_tree);
}
