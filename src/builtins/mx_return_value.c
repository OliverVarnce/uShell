#include "ush.h"

char *mx_return_value(char **str, t_variable **var_tree) {
    t_variable *tmp = *var_tree;

    while (tmp) {
        if (mx_strcmp(*str, tmp->name) == 0) {
            mx_strdel(str);
            return tmp->value;
        }
        tmp = tmp->next;
    }
    mx_strdel(str);
    return 0;
}

char *mx_return_value2(const char *str, t_variable **var_tree) {
    t_variable *tmp = *var_tree;

    while (tmp) {
        if (mx_strcmp(str, tmp->name) == 0)
            return tmp->value;
        tmp = tmp->next;
    }
    return 0;
}
