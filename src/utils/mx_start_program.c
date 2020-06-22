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
    for (; i < mx_strlen(s[0]); i++){
        a = a * 10 + (s[0][i] - '0');
    }
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

static bool check_if_env_have(char *name, t_list **environ) {
    t_list *environ_check = *environ;

    while (environ_check) {
        if (mx_strcmp(((t_variable *)environ_check->data)->name, name) == 0)
            return false;
        else
            environ_check = environ_check->next;
    }
    return true;
}

static void check_env(t_list **environ) {
    char *tmp = 0;

    if (check_if_env_have("PWD", environ)) {
        tmp = getcwd(NULL, 0);;
        mx_push_env(environ, mx_strdup("PWD"),
                    tmp, mx_strjoin("PWD=", tmp));
    }
    if (check_if_env_have("OLDPWD", environ)) {
        tmp = getcwd(NULL, 0);
        mx_push_env(environ, mx_strdup("OLDPWD"), tmp,
                    mx_strjoin("OLDPWD=", tmp));
    }
    if (check_if_env_have("SHLVL", environ)) {
        tmp = mx_strdup("1");
        mx_push_env(environ, mx_strdup("SHLVL"), tmp,
                    mx_strjoin("SHLVL=", tmp));
    }
}

void mx_start_program(t_list **environ, char **env) {
    int i = -1;
    char **envvar = 0;
    char *tmp = 0;
    t_variable *var = 0;

    while (env[++i]) {
        var = (t_variable *)malloc(sizeof(t_variable));
        envvar = mx_strsplit(env[i], '=');
        var->name = envvar[0];
        var->value = mx_strdup(&env[i][mx_strlen(var->name) + 1]);
        tmp = create_mem(envvar[0], &envvar[1], env[i], &(var->value));
        var->is_env = true;
        var->mem = tmp;
        putenv(tmp);
        mx_push_back(environ, var);
        free(envvar[1]);
        free(envvar);
    }
    check_env(environ);
}
