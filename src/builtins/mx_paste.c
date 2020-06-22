#include "ush.h"

void mx_paste(t_ush *ush, char *chars) {
    if (chars[0] == 27)
        mx_not_ascii(chars, ush);
    else {
        mx_clean_terminal(MX_USH, ush->input->inplen, ush->input->endpoint, ush->input->comands[ush->input->id]);
        for (int i = 0; i < 4 && chars[i] != 0; i++)
            mx_one_symbol(&(ush->input->comands[ush->input->id]), chars[i], &(ush->input->inplen), ush->input->endpoint);
    }
}
