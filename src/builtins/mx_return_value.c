#include "ush.h"

char *mx_return_value(char **str, t_list **var_tree) {
    t_list *tmp = *var_tree;

    while (tmp) {
        if (mx_strcmp(*str, ((t_variable*)tmp->data)->name) == 0) {
            mx_strdel(str);
            return ((t_variable *)tmp->data)->value;
        }
        tmp = tmp->next;
    }
    mx_strdel(str);
    return 0;
}

char *mx_return_value2(const char *str, t_list **var_tree) {
    t_list *tmp = *var_tree;

    while (tmp) {
        if (mx_strcmp(str, ((t_variable*)tmp->data)->name) == 0)
            return ((t_variable*)tmp->data)->value;
        tmp = tmp->next;
    }
    return 0;
}
