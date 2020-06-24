#include "ush.h"

static bool name_comand(char tmp) {
    char check = tmp >> 7;

    if ((tmp > 47 && tmp < 58) || (tmp > 64 && tmp <91) || tmp == '~')
        return 1;
    if ((tmp > 96 && tmp < 123) || tmp == 46 || tmp == '/' || tmp == '.')
        return 1;
    if (tmp == '+' || tmp == '-' || tmp == '_')
        return 1;
    if (check != 0)
        return 1;
    else
        return 0;
}

static char *create_str_comand(char *parsing) {
    int inplen;
    char *temp_str = 0;

    if (parsing == 0)
        return mx_strnew(0);
    inplen = mx_strlen(parsing) - 1;
    while (inplen > -1 && name_comand(parsing[inplen]))
        inplen--;
    if (inplen == -1)
        temp_str =  mx_strjoin("\r", parsing);
    else
        temp_str = mx_strdup(&parsing[inplen]);
    while (inplen > -1 && parsing[inplen] == ' ')
        inplen--;
    if (inplen == -1)
        temp_str[0] = '\r';
    else
        temp_str[0] = parsing[inplen];
    return temp_str;
}

char *mx_mini_parser_tab(char *parsing, t_ush *ush) {
    char *tem_str = create_str_comand(parsing);
    int pos = 0;
    char if_comand = 0;
    char *tmp = 0;

    if (mx_strstr(tem_str, "/"))
        tem_str[0] = '1';
    if (tem_str[0] != 0 && tem_str[1] == '~') {
        pos = 0;
        tmp = mx_strdup(&tem_str[1]);
        if_comand = tem_str[0];
        mx_strdel(&tem_str);
        mx_home(&tmp, &pos, ush);
        tem_str = mx_strjoin("\r", tmp);
        mx_strdel(&tmp);
        tem_str[0] = if_comand;
    }
    return tem_str;
}
