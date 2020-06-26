#include "ush.h"

static void chenge_var(t_var *var, char *name) {
    while (var) {
        if (strcmp(name, var->name) == 0) {
            var->flag = 0;
            break;
        }
        var = var->next;
    }
}

int mx_del_variable_env(char *s1, char *s2, t_var *var, int *i) {
    char *name = NULL;

    s1++;
    if (*s1 == 'i')
        for (; *s1 == 'i'; s1++);
    if (*s1 == 'u' && *(s1 + 1) != '\0') {
        s1++;
        name = mx_strdup(s1);
    }
    else {
        (*i)++;
        if (s2) {
            name = mx_strdup(s2);
        }
    }
    if (name == NULL)
        return 1;
    chenge_var(var, name);
    free(name);
    return 0;
}
