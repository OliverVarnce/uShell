#include "ush.h"

void mx_paste_nonascii(t_ush *ush, char *c) {
    if (c[0] == 27)
        mx_not_ascii(c, ush);
    else {
        mx_clean_terminal(MX_USH, ush->input->inplen, ush->input->endpoint, ush->input->comands[ush->input->id]);
        for (int i = 0; i < 4 && c[i] != 0; i++)
            mx_one_symbol(&(ush->input->comands[ush->input->id]), c[i], &(ush->input->inplen), ush->input->endpoint);
    }
}
