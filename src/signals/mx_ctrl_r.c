#include "ush.h"

static unsigned int mx_read_keyb_and_prinitng(t_ush *ush, int index,
                                                  int i, char *tmp) {
    unsigned int ch = 0;

    if (index != ush->input->maxcmd + 1)
        mx_terminal_stdout(MX_USH, mx_strlen(ush->input->comands[index]) + 1, 0,
                           ush->input->comands[index]);
    else
        mx_terminal_stdout(MX_USH, 1, 0, "");
    mx_printstr("\n");
    mx_terminal_stdout(MX_SEARCH, i, 0, tmp);
    ch = mx_get_char();
    mx_clean_terminal(MX_SEARCH, i, 0, tmp);
    mx_print_esc("1A");
    return ch;
}

static int search_comand(t_ush *ush, int index, char *tmp) {
    int index_comand = ush->input->maxcmd + 1;
    int str_len_comand = 0;

    if (index != ush->input->maxcmd + 1) {
        str_len_comand = mx_strlen(ush->input->comands[index]) + 1;
        mx_clean_terminal(MX_USH, str_len_comand, 0, ush->input->comands[index]);
    }
    else
        mx_clean_terminal(MX_USH, 1, 0, "");
    for (int y = 0; index_comand == ush->input->maxcmd + 1 && ush->input->comands[y]; y++)
        if (mx_strstr(ush->input->comands[y], tmp) != 0)
            index_comand = y;
    return index_comand;
}

void mx_ctrl_r(t_ush *ush) {
    unsigned int ch = 0; 
    char *tmp = mx_strnew(0);
    int i = 1;
    bool check = 1;
    int index = ush->input->maxcmd + 1;

    while (check) {
        ch = mx_read_keyb_and_prinitng(ush, index, i, tmp);
        if (ch > 31 && ch < 128)
            mx_one_symbol(&tmp, ch, &i, 0);
        else
            check = 0;
        index = search_comand(ush, index, tmp);
    }
    if (index != ush->input->maxcmd + 1) {
        ush->input->id = index;
        ush->input->endpoint = 0;
        ush->input->inplen = mx_strlen(ush->input->comands[ush->input->id]) + 1;
    }
    mx_strdel(&tmp);
}
