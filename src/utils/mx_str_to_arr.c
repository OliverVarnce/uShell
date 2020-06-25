#include "ush.h"

void mx_str_to_arr(char ***strings, char *str) {
    int i = 0;

    if ((strings == 0) || (str == 0))
        return;
    if (*strings == 0) {
        *strings = (char **)malloc(sizeof(char *) * 2);
        (*strings)[0] = str;
        (*strings)[1] = 0;
        return;
    }
    for (; (*strings)[i];)
        i++;
    *strings = (char **)mx_realloc(*strings, sizeof(char *) * (i+ 2));
    (*strings)[i] = str;
    (*strings)[i + 1] = 0;
    return;
}
