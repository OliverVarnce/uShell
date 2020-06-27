#include "ush.h"

char *mx_arr_str_to_str(char **strings) {
    char *new_str = 0;
    int i = -1;

    for (; strings[++i];) {
        new_str = mx_str_concatenation(new_str, strings[i]);
        if (strings[i + 1])
            new_str = mx_str_concatenation(new_str, " ");
    }
    return new_str;
}
