#include "ush.h"

static bool symbols(char c) {
    if (c == 34 || c == 39 || c == 96)
        return 1;
    return 0;
}

static void useflag(char flag) {
    mx_printerr("u$h: parse error near | ");
    mx_printerr(&flag);
    mx_printerr(" |\n");
}

static bool operators(char *s, int *pos, int flag) {
    if (flag != ' ')
        return 0;
    if (s[pos[0]] == '|' || s[pos[0]] == '<'
        || s[pos[0]] == '>' || s[pos[0]] == '&')
        if (mx_check_symbol(s, pos[0], s[pos[0]])) {
            pos[0]--;
            return 1;
        }
    return 0;
}

static int spec_symbol(char *s, int *pos, int last, int flag) {
    int input_flag = flag;

    if (symbols(s[pos[0]]) && mx_check_symbol(s, pos[0], s[pos[0]])) {
        pos[0]++;
        input_flag = mx_last_flag(s, pos, last, input_flag);
    } 
    else if (pos[0] > 0 && s[*pos] == 40 
             && mx_check_symbol(s, pos[0] - 1, '$')) {
        pos[0]++;
        input_flag = mx_last_flag(s, pos, last, ')');
    }
    return input_flag;
}

int mx_checker_flag(char *s, int *pos, int last, int flag) {
    int find_flag = flag;

    while (pos[0] <= last) {
        find_flag = s[pos[0]];
        if (mx_check_symbol(s, pos[0], flag) || operators(s, pos, flag)) {
            return 0;
        }
        else if ((symbols(s[*pos])
                  && mx_check_symbol(s, pos[0], s[pos[0]]))
                  || (pos[0] > 0 && s[pos[0]] == 40 
             && mx_check_symbol(s, pos[0] - 1, '$')))
             find_flag = spec_symbol(s, pos, last, find_flag);
        else
            (pos[0])++;
    }
    if (flag != 32)
        useflag(flag);
    return flag;
}
