#include "ush.h"

void mx_push_front_res(t_variable **list, t_variable *new_head) {
    new_head->next = *list;
    *list = new_head;
}

void mx_push_env(t_variable **var_tree, char *name, char *value, char *mem) {
    t_variable *var = (t_variable*) malloc(sizeof(t_variable));

    var->value = value;
    var->is_env = true;
    var->name = name;
    var->mem = mem;
    putenv(var->mem);
    var->next = NULL;
    mx_push_front_res(var_tree, var);
}
