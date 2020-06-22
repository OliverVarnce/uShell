#include "ush.h"

static void change_variteble(t_variable *noda, char *name, char *value) {
    char *tmp = 0;

    mx_strdel(&((t_variable*)noda)->name);
    mx_strdel(&((t_variable*)noda)->value);
    noda->name = name;
    noda->value = value;
    if (noda->is_env) {
        tmp = mx_strjoin(name, "=");
        tmp = mx_strjoin2(tmp, value);
        mx_strdel(&(noda->mem));
        noda->mem = tmp;
        putenv(tmp);
    }
}

void mx_serch_list(t_list **environ, char *name, char *value) {
    t_list *environ_temp = *environ;
    t_variable *var = 0;
    int i = 1;

    while (i == 1 && environ_temp) {
        if (mx_strcmp(((t_variable*)environ_temp->data)->name, name) == 0) {
            change_variteble(environ_temp->data, name, value);
            i = 0;
        }
        else
            environ_temp = environ_temp->next;
    }
    if (!(environ_temp)) {
        var = (t_variable*)malloc(sizeof(t_variable));
        var->mem = 0;
        var->is_env = false;
        var->name = name;
        var->value = value;
        mx_push_back(environ, var);
    }
}
