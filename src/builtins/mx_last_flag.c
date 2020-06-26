#include "ush.h"

static int flang_string(char *s, int *pos, int end, int flag) {
    while (*pos < end) {
        if (mx_check_symbol(s, *pos, 39))
            return 0;
        (*pos)++;
    }
    mx_printerr("u$h: parse error near | \' |\n");
    return flag;
}

int mx_last_flag(char *s, int *pos, int end, int flag) {
    int check_flag = 0;

    if (flag == 39)
        check_flag = flang_string(s, pos, end, flag);
    else
        check_flag = mx_checker_flag(s, pos, end, flag);
    (*pos)++;
    return check_flag;
}
