#include "ush.h"

static int mx_handle_events(char ch) {
    if (ch == KEY_ENTER) {
        return KEY_ENTER;
    }
    if (ch == CTRL_I)
        return 9;
    if (ch == CTRL_D) {
        return -1;
    }
    if (ch == CTRL_Z) {
        write(1, "\a", 1);
    }
    if (ch == CTRL_C)
        return 2;
    if (ch == CTRL_R)
        return 18;
    return 0;
}

static void special_symbols(unsigned int ch, t_ush *ush) {
    int str_pos = MX_STR_LEN - MX_STR_POS - 1;
    char *str_tab = 0;

    if (MX_SYMBOL != 9 && ch == 9) {
        str_tab = mx_strndup(MX_STR,str_pos);
        mx_clean_terminal(MX_USH, MX_STR_LEN, MX_STR_POS, MX_STR);
        ush->input->comand_tab = mx_key_tab(str_tab, &MX_STR, ush);
        ush->input->pos_tab = 0;
    }
    if (MX_SYMBOL == 9 && ch == 9) {
        mx_clean_terminal(MX_USH, MX_STR_LEN, MX_STR_POS, MX_STR);
        mx_key_duble_tab(&MX_STR, ush->input->comand_tab, ush);
    }
    MX_SYMBOL = mx_handle_events(ch);
    if (MX_SYMBOL == 18) {
        mx_clean_terminal(MX_USH, MX_STR_LEN, MX_STR_POS, MX_STR);
        mx_ctrl_r(ush);
    }
}

static int ctrl_enter_d_c(t_ush *ush) {
    if (MX_SYMBOL == -1) {
        mx_clean_space_in_term(MX_STR, ush, "exit");
        return 0;
    }
    else if (MX_SYMBOL == 2) {
        mx_clean_terminal(MX_USH, MX_STR_LEN, MX_STR_POS, MX_STR);
        return 2;
    }
    else if (MX_SYMBOL == KEY_ENTER) {
        mx_clean_space_in_term(MX_STR, ush, MX_STR);
        if (mx_strlen(MX_STR) != 0) {
            if (ush->history == NULL
                || mx_strcmp(MX_STR, ush->history->data) != 0)
                mx_push_front(&ush->history, mx_strdup(MX_STR));
            return 1;
        }
    }
    return 3;
}

int mx_ascii(t_ush *ush, char *chars, unsigned int ch) {
    int spec_symbol = 3;

    if (ch < 32) {
        special_symbols(ch, ush);
        if (MX_SYMBOL == -1 || MX_SYMBOL == 2 || MX_SYMBOL == 13)
            spec_symbol = ctrl_enter_d_c(ush);
        else
            chars[2] = 10;
    }
    else {
        mx_clean_terminal(MX_USH, MX_STR_LEN, MX_STR_POS, MX_STR);
        mx_one_symbol(&(MX_STR), ch, &(MX_STR_LEN), MX_STR_POS);
    }
    return spec_symbol;
}
