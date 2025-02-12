#include "ush.h"

static void join_val(t_variable *noda, char *name, char *value) {
    char *buf = 0;

    mx_strdel(&(noda->name));
    mx_strdel(&(noda->value));
    noda->name = name;
    noda->value = value;
    if (noda->is_env) {
        buf = mx_strjoin(name, "=");
        buf = mx_str_concatenation(buf, value);
        mx_strdel(&(noda->mem));
        noda->mem = buf;
        putenv(buf);
    }
}

void mx_find_cur_list(t_variable **var_tree, char *name, char *value) {
    t_variable *var_tree_temp = *var_tree;
    t_variable *var = 0;
    int i = 1;

    while (i == 1 && var_tree_temp) {
        if (mx_strcmp(var_tree_temp->name, name) == 0) {
            join_val(var_tree_temp, name, value);
            i = 0;
        }
        else
            var_tree_temp = var_tree_temp->next;
    }
    if (!(var_tree_temp)) {
        var = (t_variable*)malloc(sizeof(t_variable));
        var->mem = 0;
        var->is_env = false;
        var->name = name;
        var->value = value;
        var->next = NULL;
        mx_push_back_res(var_tree, var);
    }
}
