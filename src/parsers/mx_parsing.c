#include "ush.h"

void mx_parsing(char *str, t_ush *ush) {
    int end = mx_strlen(str);
    char *tmp = mx_parsing_input(str);
    char **comands = 0;

    if (tmp == 0) {
        return;
    }
    if (mx_check_symbol(str, end -1, '\\')) {
        mx_strdel(&tmp);
        mx_printerr("u$h: parse error near | \\ |\n");
        return;
    }
    comands = mx_create_comands(tmp, end);
    mx_execute(comands, ush);
    mx_del_strarr(&comands);
}
