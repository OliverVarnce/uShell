#include "ush.h"

static int mx_events(char ch) {
    if (ch == KEY_ENTER)
        return KEY_ENTER;
    if (ch == CTRL_I)
        return 9;
    if (ch == CTRL_D)
        return -1;
    if (ch == CTRL_Z)
        mx_printstr("\a");
    if (ch == CTRL_C)
        return 2;
    if (ch == CTRL_R)
        return 18;
    return 0;
}

static void mx_special_smbls(unsigned int ch, t_ush *ush) {
    int str_pos = ush->input->inplen - ush->input->endpoint - 1;
    char *str_tab = 0;

    if (ush->input->symb != 9 && ch == 9) {
        str_tab = mx_strndup(ush->input->comands[ush->input->id],str_pos);
        mx_clean_terminal(MX_USH, ush->input->inplen, ush->input->endpoint,
                ush->input->comands[ush->input->id]);
        ush->input->comand_tab = mx_key_tab(str_tab,
                &ush->input->comands[ush->input->id], ush);
        ush->input->tabposition = 0;
    }
    if (ush->input->symb == 9 && ch == 9) {
        mx_clean_terminal(MX_USH, ush->input->inplen, ush->input->endpoint,
                ush->input->comands[ush->input->id]);
        mx_key_duble_tab(&ush->input->comands[ush->input->id],
                ush->input->comand_tab, ush);
    }
    ush->input->symb = mx_events(ch);
    if (ush->input->symb == 18) {
        mx_clean_terminal(MX_USH, ush->input->inplen, ush->input->endpoint,
                ush->input->comands[ush->input->id]);
        mx_ctrl_r(ush);
    }
}

static int mx_ctrl_enter_d_c(t_ush *ush) {
    if (ush->input->symb == -1) {
        mx_clean_space_in_term(ush->input->comands[ush->input->id], ush,
                "exit");
        return 0;
    }
    else if (ush->input->symb == 2) {
        mx_clean_terminal(MX_USH, ush->input->inplen, ush->input->endpoint,
                ush->input->comands[ush->input->id]);
        return 2;
    }
    else if (ush->input->symb == KEY_ENTER) {
        mx_clean_space_in_term(ush->input->comands[ush->input->id], ush,
                ush->input->comands[ush->input->id]);
        if (mx_strlen(ush->input->comands[ush->input->id]) != 0) {
            if (ush->history == NULL
                || mx_strcmp(ush->input->comands[ush->input->id],
                        ush->history->data) != 0)
                mx_push_front(&ush->history,
                        mx_strdup(ush->input->comands[ush->input->id]));
            return 1;
        }
    }
    return 3;
}

int mx_ascii(t_ush *ush, char *chars, unsigned int ch) {
    int spec_symbol = 3;

    if (ch < 32) {
        mx_special_smbls(ch, ush);
        if (ush->input->symb == -1 || ush->input->symb == 2 ||
            ush->input->symb == 13)
            spec_symbol = mx_ctrl_enter_d_c(ush);
        else
            chars[2] = 10;
    }
    else {
        mx_clean_terminal(MX_USH, ush->input->inplen, ush->input->endpoint,
                ush->input->comands[ush->input->id]);
        mx_one_symbol(&(ush->input->comands[ush->input->id]), ch,
                &(ush->input->inplen), ush->input->endpoint);
    }
    return spec_symbol;
}
