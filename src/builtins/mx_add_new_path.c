#include "ush.h"

char *mx_add_new_path(char *path, char *new_part) {
    int len_path = mx_strlen(path);
    char *new_path = 0;

    if (path[len_path - 1] != '/')
        new_path = mx_strjoin(path, "/");
    new_path = mx_strjoin2(new_path, new_part);
    free(path);
    return new_path;
}
