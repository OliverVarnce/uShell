#include "ush.h"

static void not_id_0(char **str, char **comands, t_ush *ush) {
    for (int i = 0; comands[ush->input->tabposition - 1][i]; i++)
        mx_one_symbol(str, 127, &(ush->input->inplen), ush->input->endpoint);
    if (comands[ush->input->tabposition] != 0) {
        for (int i = 0; comands[ush->input->tabposition][i]; i++)
            mx_one_symbol(str, comands[ush->input->tabposition][i],
                          &(ush->input->inplen), ush->input->endpoint);
        ush->input->tabposition++;
    }
    else {
        for (int i = 0; comands[0][i]; i++)
            mx_one_symbol(str, comands[0][i], &(ush->input->inplen), ush->input->endpoint);
        ush->input->tabposition = 1;
    }
}

void mx_key_duble_tab(char **str, char **comands, t_ush *ush) {
    if (comands != 0 && comands[0] != 0) {
        if (ush->input->tabposition == 0 && comands[0] != 0) {
            for (int i = 0; comands[0][i]; i++)
                mx_one_symbol(str, comands[0][i], &(ush->input->inplen), ush->input->endpoint);
            if (ush->input->endpoint != 0) {
                mx_one_symbol(str, ' ', &(ush->input->inplen), ush->input->endpoint);
                ush->input->endpoint++;
            }
            ush->input->tabposition++;
        }
        else
            not_id_0(str,comands, ush);
    }
    else
        write(1,"\a", 1);
}
