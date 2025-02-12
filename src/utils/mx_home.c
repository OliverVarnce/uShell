#include "ush.h"

static bool is_operator1(char c) {
    if (c == '|' || c == '&' || c == '>' || c == '<' || c == ' ')
        return false;
    if (c == 0 || c == '/')
        return false;
    return true;
}

static bool is_operator2(char c) {
    if (c == '$' || c == '=' || c == 92 || c == 34 || c == 39 || c == 96)
        return false;
    return true;
} 

static void read_user(char **user) {
    struct passwd *check = getpwnam(*user);

    mx_strdel(user);
    if (check)
        *user = mx_strdup(check->pw_dir);
    check = 0;
}

static char *env_param(char **string, int *i, t_ush *processes) {
    char *str = *string;
    char *home = 0;

    if (str[*i + 1] == 0 || str[*i + 1] == ' ' || str[*i + 1] == '/')
        home = mx_strdup("HOME");
    else if ((str[*i + 1] == '+' || str[*i + 1] == '-') && (str[*i + 2] == 0
              || str[*i + 2] == ' ' || str[*i + 2] == '/')) {
        if (str[*i + 1] == '+')
            home = mx_strdup("PWD");
        else 
            home = mx_strdup("OLDPWD");
        (*i)++;
    }
    if (home) {
        home = mx_strdup(mx_return_var(&home, &processes->var_tree));
        (*i)++;
        if (home == 0)
            home = mx_strnew(0);
    }
    return home;
}

void mx_home(char **string, int *i, t_ush *processes) {
    char *home = 0;
    int new_position = *i;

    if (*i != 0)
        return;
    home = env_param(string, &new_position, processes);
    if (new_position == 0) {
        for (; is_operator1(string[0][++new_position]) && is_operator2(string[0][new_position]);)
        if (is_operator2(string[0][new_position]))
            home = mx_strndup(&string[0][*i + 1], new_position - *i - 1);
        if (home)
            read_user(&home);
    }
    if (home) {
        mx_replace(string, *i, new_position, home);
        *i += mx_strlen(home);
        mx_strdel(&home);
    }
}
