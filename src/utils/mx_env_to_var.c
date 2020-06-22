#include "ush.h"

static t_var *node(t_list *environ, t_var *var) {
    var->next = malloc(sizeof(t_var));
    var = var->next;
    var->flag = 1;
    var->value = strdup(((t_variable*)environ->data)->mem);
    var->name = mx_strdup(((t_variable*)environ->data)->name);
    var->next = NULL;
    return var;
}

t_var *mx_environ_to_var(t_list *environ) {
    t_var *var = malloc(sizeof(t_var));;
    t_var *save = var;

    var->name = NULL;
    var->flag = 0;
    var->next = NULL;
    var->value = NULL;
    for (;environ; environ = environ->next) {
        if (var->value == NULL && ((t_variable*)environ->data)->is_env) {
            var->value = strdup(((t_variable*)environ->data)->mem);
            var->name = mx_strdup(((t_variable*)environ->data)->name);
            var->flag = 1;
        }
        else if (((t_variable*)environ->data)->is_env)
            var = node(environ, var);
    }
    return save;
}

