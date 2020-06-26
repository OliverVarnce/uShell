#include "ush.h"

char* mx_del_last_rank(char *path) {
    char *new = 0;
    int len = mx_strlen(path);
    int i = len;

    while (path[--i] && path[i] != '/')
        path[i] = 0;
    if ((path[i] == '/') && (i != 0))
        path[i] = 0;
    new = mx_strdup(path);
    free(path);
    return new;
}
