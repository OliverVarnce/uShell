#include "ush.h"

static void havent_id(char **s, char **com, t_ush *ush) {
    for (int i = 0; com[ush->input->tabposition - 1][i]; i++)
        mx_one_symbol(s, 127, &(ush->input->inplen), ush->input->endpoint);
    if (com[ush->input->tabposition] != 0) {
        for (int i = 0; com[ush->input->tabposition][i]; i++)
            mx_one_symbol(s, com[ush->input->tabposition][i],
                          &(ush->input->inplen), ush->input->endpoint);
        ush->input->tabposition++;
    }
    else {
        for (int i = 0; com[0][i]; i++)
            mx_one_symbol(s, com[0][i], &(ush->input->inplen), ush->input->endpoint);
        ush->input->tabposition = 1;
    }
}

void mx_many_tabs(char **s, char **com, t_ush *ush) {
    if (com != 0 && com[0] != 0) {
        if (ush->input->tabposition == 0 && com[0] != 0) {
            for (int i = 0; com[0][i]; i++)
                mx_one_symbol(s, com[0][i], &(ush->input->inplen), ush->input->endpoint);
            if (ush->input->endpoint != 0) {
                mx_one_symbol(s, ' ', &(ush->input->inplen), ush->input->endpoint);
                ush->input->endpoint++;
            }
            ush->input->tabposition++;
        }
        else
            havent_id(s,com, ush);
    }
    else
        write(1,"\a", 1);
}
