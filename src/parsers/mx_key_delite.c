#include "ush.h"

void mx_key_delite(t_ush *ush) {
    int i;
    int sum = mx_bit_sumbol(&ush->input->cmds[ush->input->id][ush->input->inplen - ush->input->endpoint - 1]);

    mx_clean_terminal(MX_USH, ush->input->inplen, ush->input->endpoint, ush->input->cmds[ush->input->id]);
    for (;sum > 0; sum--) {
        i = ush->input->endpoint;
        ush->input->endpoint--;
        while (i > 0) {
            ush->input->cmds[ush->input->id][ush->input->inplen - i - 1] = ush->input->cmds[ush->input->id][ush->input->inplen - i];
            i--;
        }
        ush->input->inplen--;
    }
    ush->input->cmds[ush->input->maxcmd][ush->input->inplen - 1] = 0;
}
