#include "ush.h"

static bool check_av(char *str) {
    for (int i = 0 ; str[i]; i++)
        if (str[i] == '=') {
            mx_printerr("unset: ");
            mx_printerr(str);
            mx_printerr(": invalid parameter name\n");
            return 0;
        }
    return 1;
}

static bool if_av(void *s1, void *s2) {
    char *tmp1 = s1;
    char *tmp2 = ((t_variable *)s2)->name;

    if (mx_strcmp(tmp1, tmp2) == 0)
        return 1;
    else
        return 0;
}

void mx_unset(char **av, t_variable **var_tree, t_ush *ush) {
    ush->last_status = 0;
    for (int i = 1; av[i]; i++) {
        if (check_av(av[i])) {
            mx_pop_list(var_tree, av[i], if_av);
        }
    }
}
