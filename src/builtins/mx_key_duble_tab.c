#include "ush.h"

static void not_id_0(char **str, char **cmds, t_ush *ush) {
    for (int i = 0; cmds[ush->input->tabposition - 1][i]; i++)
        mx_one_symbol(str, 127, &(ush->input->inplen), ush->input->endpoint);
    if (cmds[ush->input->tabposition] != 0) {
        for (int i = 0; cmds[ush->input->tabposition][i]; i++)
            mx_one_symbol(str, cmds[ush->input->tabposition][i],
                          &(ush->input->inplen), ush->input->endpoint);
        ush->input->tabposition++;
    }
    else {
        for (int i = 0; cmds[0][i]; i++)
            mx_one_symbol(str, cmds[0][i], &(ush->input->inplen), ush->input->endpoint);
        ush->input->tabposition = 1;
    }
}

void mx_key_duble_tab(char **str, char **cmds, t_ush *ush) {
    if (cmds != 0 && cmds[0] != 0) {
        if (ush->input->tabposition == 0 && cmds[0] != 0) {
            for (int i = 0; cmds[0][i]; i++)
                mx_one_symbol(str, cmds[0][i], &(ush->input->inplen), ush->input->endpoint);
            if (ush->input->endpoint != 0) {
                mx_one_symbol(str, ' ', &(ush->input->inplen), ush->input->endpoint);
                ush->input->endpoint++;
            }
            ush->input->tabposition++;
        }
        else
            not_id_0(str,cmds, ush);
    }
    else
        write(1,"\a", 1);
}
