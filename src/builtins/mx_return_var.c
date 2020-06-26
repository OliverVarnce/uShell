#include "ush.h"

char *mx_return_var(char **s, t_variable **var_tree) {
    t_variable *tmp = *var_tree;

    while (tmp) {
        if (mx_strcmp(*s, tmp->name) == 0) {
            mx_strdel(s);
            return tmp->value;
        }
        tmp = tmp->next;
    }
    mx_strdel(s);
    return 0;
}

char *mx_return_var2(const char *s, t_variable **var_tree) {
    t_variable *tmp = *var_tree;

    while (tmp) {
        if (mx_strcmp(s, tmp->name) == 0)
            return tmp->value;
        tmp = tmp->next;
    }
    return 0;
}
