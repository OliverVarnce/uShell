#include "ush.h"

char *mx_arrstr_to_str(char **strs) {
    char *new_str = 0;
    int i = -1;

    for (; strs[++i];) {
        new_str = mx_strjoin2(new_str, strs[i]);
        if (strs[i + 1])
            new_str = mx_strjoin2(new_str, " ");
    }
    return new_str;
}
