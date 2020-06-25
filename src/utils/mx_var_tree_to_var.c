#include "ush.h"

static t_var *node(t_variable *var_tree, t_var *var) {
    var->next = malloc(sizeof(t_var));
    var = var->next;
    var->flag = 1;
    var->value = strdup(var_tree->mem);
    var->name = mx_strdup(var_tree->name);
    var->next = NULL;
    return var;
}

t_var *mx_var_tree_to_var(t_variable *var_tree) {
    t_var *var = malloc(sizeof(t_var));;
    t_var *save = var;

    var->name = NULL;
    var->flag = 0;
    var->next = NULL;
    var->value = NULL;
    for (; var_tree; var_tree = var_tree->next) {
        if (var->value == NULL && var_tree->is_env) {
            var->value = strdup(var_tree->mem);
            var->name = mx_strdup(var_tree->name);
            var->flag = 1;
        }
        else if (var_tree->is_env)
            var = node(var_tree, var);
    }
    return save;
}

