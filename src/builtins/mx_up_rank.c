#include "ush.h"

char *mx_up_rank(char *path, char *part) {
    int len_path = mx_strlen(path);
    char *full_path = 0;

    if (path[len_path - 1] != '/')
        full_path = mx_strjoin(path, "/");
    full_path = mx_strjoin2(full_path, part);
    free(path);
    return full_path;
}
