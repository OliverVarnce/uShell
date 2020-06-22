#include "ush.h"

static unsigned int mx_read_keyb_and_prinitng(t_ush *ush, int index,
                                                  int i, char *tmp) {
    unsigned int ch = 0;

    if (index != MX_MAX_COMAND + 1)
        mx_terminal_out(MX_USH, mx_strlen(MX_COMMAND[index]) + 1, 0,
                           MX_COMMAND[index]);
    else
        mx_terminal_out(MX_USH, 1, 0, "");
    mx_printstr("\n");
    mx_terminal_out(MX_SEARCH, i, 0, tmp);
    ch = mx_getchar();
    mx_clean_terminal(MX_SEARCH, i, 0, tmp);
    mx_print_esc("1A");
    return ch;
}

static int search_comand(t_ush *ush, int index, char *tmp) {
    int index_comand = MX_MAX_COMAND + 1;
    int str_len_comand = 0;

    if (index != MX_MAX_COMAND + 1) {
        str_len_comand = mx_strlen(MX_COMMAND[index]) + 1;
        mx_clean_terminal(MX_USH, str_len_comand, 0, MX_COMMAND[index]);
    }
    else
        mx_clean_terminal(MX_USH, 1, 0, "");
    for (int y = 0; index_comand == MX_MAX_COMAND + 1 && MX_COMMAND[y]; y++)
        if (mx_strstr(MX_COMMAND[y], tmp) != 0)
            index_comand = y;
    return index_comand;
}

void mx_ctrl_r(t_ush *ush) {
    unsigned int ch = 0; 
    char *tmp = mx_strnew(0);
    int i = 1;
    bool check = 1;
    int index = MX_MAX_COMAND + 1;

    while (check) {
        ch = mx_read_keyb_and_prinitng(ush, index, i, tmp);
        if (ch > 31 && ch < 128)
            mx_one_symbol(&tmp, ch, &i, 0);
        else
            check = 0;
        index = search_comand(ush, index, tmp);
    }
    if (index != MX_MAX_COMAND + 1) {
        MX_ID = index;
        MX_STR_POS = 0;
        MX_STR_LEN = mx_strlen(MX_STR) + 1;
    }
    mx_strdel(&tmp);
}
