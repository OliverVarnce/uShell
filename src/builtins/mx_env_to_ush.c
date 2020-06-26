#include "ush.h"

char **mx_env_to_ush(t_var *var) {
    t_var *save = var;
    int count = 0;
    char **env = NULL;

    if (var == NULL)
        return NULL;
    for ( ; var; var = var->next) {
        if (var->flag)
            count++;
    }
    var = save;
    env = malloc(sizeof(char *) * (count + 1));
    env[count] = NULL;
    for (count = 0; var; var = var->next) {
        if (var->flag) {
            env[count] = mx_strdup(var->value);
            count++;
        }
    }
    return env;
}
