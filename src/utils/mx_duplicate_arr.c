#include "ush.h"

char **mx_duplicate_arr(char **strings) {
    char **new_arr = 0;
    int i = -1;
    int len = 0;

    if (strings == 0)
        return 0;
    for (; strings[len]; len++);
    new_arr = (char **)malloc(sizeof(char *) * (len + 1));
    for (; strings[++i];)
        new_arr[i] = mx_strdup(strings[i]);
    
    new_arr[i] = 0;
    return new_arr;
}
