#include "ush.h"

void mx_add_to_strarr(char ***strs, char *str) {
    int count = 0;

    if ((strs == 0) || (str == 0))
        return;
    if (*strs == 0) {
        *strs = (char **)malloc(sizeof(char *) * 2);
        (*strs)[0] = str;
        (*strs)[1] = 0;
        return;
    }
    for (; (*strs)[count];)
        count++;
    *strs = (char **)mx_realloc(*strs, sizeof(char *) * (count+ 2));
    (*strs)[count] = str;
    (*strs)[count + 1] = 0;
    return;
}
