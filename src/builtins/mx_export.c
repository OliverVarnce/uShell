#include "ush.h"

static void new_node(t_variable **var_tree, char *name, char *value, char *tmp) {
    t_variable *node = malloc(sizeof(t_variable));

    node->name = name;
    node->value = value;
    node->mem = value == 0 ? tmp : mx_str_concatenation(tmp, value);
    node->is_env = true;
    putenv(node->mem);
    node->next = NULL;
    mx_push_back_res(var_tree, node);
}

static void get_param(t_variable **var_tree, char *s) {
    int count = mx_get_char_index(s, '=');
    char *name = count == -1 ? mx_strdup(s) : mx_strndup(s, count);
    char *val = count == -1 ? 0 : mx_strdup(s + count + 1);
    t_variable *var_tree_tmp = *var_tree;
    char *tmp = mx_strjoin(name, "=");

    for (; var_tree_tmp; var_tree_tmp = var_tree_tmp->next) {
        if (strcmp(var_tree_tmp->name, name) == 0) {
            mx_charge_parametr_export(val, tmp, var_tree_tmp);
            free(name);
            free(tmp);
            return;
        }
    }
    new_node(var_tree, name, val, tmp);
}

static void swap_var(t_var *var) {
    char *name = var->name;
    char *value = var->value;
    int flag = var->flag;

    var->name = var->next->name;
    var->value = var->next->value;
    var->flag = var->next->flag;
    var->next->name = name;
    var->next->value = value;
    var->next->flag = flag;
}

static void export_help(t_variable *var_tree_tmp) {
    t_var *var = mx_var_tree_to_var(var_tree_tmp);
    t_var *tmp = var;

    for (t_var *i = var; i && var->value; i = i->next) {
        for (t_var *j = var; j->next; j = j->next) {
            if (mx_strcmp(j->name, j->next->name) > 0)
                swap_var(j);
        }
    }
    while (var && var->value) {
        mx_printstr(var->value);
        mx_printstr("\n");
        tmp = var;
        var = var->next;
        free(tmp->value);
        free(tmp->name);
        free(tmp);
    }
    free(var);
}

void mx_export(char **av, t_variable **var_tree, t_ush *ush) {
    ush->last_return = 0;
    for (int i = 0; av[i]; i++) {
        if (mx_reg(av[i], "")) {
            mx_printerr("export: not valid in this context:");
            mx_printerr(av[i]);
            ush->last_return = 1;
            return;
        }
    }
    for (int i = 1; av[i]; i++) {
        if (mx_reg(av[i], MX_REG_EXPORT))
            get_param(var_tree, av[i]);
    }
    if (av[1] == 0)
        export_help(*var_tree);
}
