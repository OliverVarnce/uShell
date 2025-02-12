#include "ush.h"

static bool is_operator1(char c) {
    if (c == '|' || c == '&' || c == '>' || c == '<'|| c == '$' || c == ' ')
        return false;
    if (c == 34 || c == 39 || c== 96 || c == 0 || c == '?')
        return false;
    if (c == '='|| c == 92)
        return false;
    return true;
}

static int end_parametr(char *str, int i) {
    int tmp = i + 1;

    while (is_operator1(str[tmp]))
        tmp++;
    if (str[tmp] == '?' && str[tmp + 1] != '(')
        tmp++;
    return tmp;
}

static void parametrchell(t_ush *processes, int *i, char **new_str) {
    int end = *i;
    int flag = 0;
    char *par_shell = 0;

    flag = mx_last_flag(*new_str, &end, mx_strlen(*new_str), '}');
    if (flag != 0) {
        mx_strdel(new_str);
        *new_str = mx_strnew(0);
        *i = 0;
    }
    else {
        mx_strdel(&par_shell);
        par_shell = mx_strndup(&new_str[0][*i + 2], end - *i - 3);
        par_shell = mx_return_var(&par_shell, &(processes->var_tree));
        mx_replace(new_str, *i, end, par_shell);
        if (par_shell)
            *i += mx_strlen(par_shell);
    }
}

static void parametrlaststatus(t_ush *processes, int *i, char **new_str, int flag) {
    char *par_shell = 0;

    par_shell = mx_itoa(processes->last_return);
    mx_replace(new_str, *i, flag, par_shell);
    if (par_shell) {
        *i += mx_strlen(par_shell);
        if (strcmp(par_shell, "1") == 0)
            mx_strdel(&par_shell);
    }
}

void mx_term_param(t_ush *processes, int *i, char **new_str) {
    int flag = end_parametr(*new_str, *i);
    char *par_shell = 0;

    par_shell = mx_strndup(&new_str[0][*i + 1], flag - *i - 1);
    if (par_shell[0] == '?') {
        if (par_shell != NULL) {
            mx_strdel(&par_shell);
        }
        parametrlaststatus(processes, i, new_str, flag);
    }
    else if (par_shell[0] == '{') {
        mx_strdel(&par_shell);
        parametrchell(processes, i, new_str);
    }
    else {
        par_shell = mx_return_var(&par_shell, &(processes->var_tree));
        mx_replace(new_str, *i, flag, par_shell);
        if (par_shell)
            *i += mx_strlen(par_shell);
    }
    (*i)--;
}
