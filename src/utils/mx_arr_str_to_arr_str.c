#include "ush.h"

static int mx_len_arr_str(char **str) {
    int count = 0;

    for (; str[count];)
        count++;
    return count;
}

void mx_arr_str_to_arr_str(char ***strings, char ***str) {
    int count = 0;
    int count2 = 0;

    if ((strings == 0) || (str == 0))
        return;
    if (*strings == 0) {
        *strings = *str;
        return;
    }
    count = mx_len_arr_str(*strings);
    count2 = mx_len_arr_str(*str);
    *strings = (char **) realloc(*strings, sizeof(char *) * (count  + count2 + 1));
    count2 = 0;
    for (; (*str)[count2];) {
        (*strings)[count++] = (*str)[count2++];
    }
    (*strings)[count] = 0;
    free(*str);
    return;
}
