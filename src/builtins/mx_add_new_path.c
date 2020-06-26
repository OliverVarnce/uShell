#include "ush.h"

char *mx_add_new_path(char *path, char *part) {
    int len = mx_strlen(path);
    char *path2 = 0;

    if (path[len - 1] != '/')
        path2 = mx_strjoin(path, "/");
    path2 = mx_strjoin2(path2, part);
    free(path);
    return path2;
}
