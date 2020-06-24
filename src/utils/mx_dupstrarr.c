#include "ush.h"

char **mx_dupstrarr(char **strs) {
    char **new_arr = 0;
    int i = -1;
    int len = 0;

    if (strs == 0)
        return 0;
    for (;strs[len];len++);
    new_arr = (char **)malloc(sizeof(char *) * (len + 1));
    for (; strs[++i];) {
        new_arr[i] = mx_strdup(strs[i]);
    }
    new_arr[i] = 0;
    return new_arr;
}
