#include "ush.h"

static int flag_in_str(char *str, int *pos, int end, int flag) {
    while (*pos < end) {
        if (mx_check_symbol(str, *pos, 39))
            return 0;
        (*pos)++;
    }
    mx_printerr("u$h: parse error near | \' |\n");
    return flag;
}

int mx_last_flag(char *s, int *pos, int end, int flag) {
    int flags = 0;

    if (flag == 39)
        flags = flag_in_str(s, pos, end, flag);
    else
        flags = mx_flang_comand(s, pos, end, flag);
    (*pos)++;
    return flags;
}
