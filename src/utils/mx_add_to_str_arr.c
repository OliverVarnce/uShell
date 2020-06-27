#include "ush.h"

void mx_add_to_str_arr(char ***strings, char *str) {
    int count = 0;

    if ((strings == 0) || (str == 0))
        return;
    if (*strings == 0) {
        *strings = (char **)malloc(sizeof(char *) * 2);
        (*strings)[0] = str;
        (*strings)[1] = 0;
        return;
    }
    for (; (*strings)[count];)
        count++;
    *strings = (char **)mx_realloc(*strings, sizeof(char *) * (count+ 2));
    (*strings)[count] = str;
    (*strings)[count + 1] = 0;
    return;
}
