#include "ush.h"

void mx_key_delite(t_ush *ush) {
    int i;
    int sum = mx_bit_sumbol(&MX_STR[MX_STR_LEN - MX_STR_POS - 1]);

    mx_clean_terminal(MX_USH, MX_STR_LEN, MX_STR_POS, MX_STR);
    for (;sum > 0; sum--) {
        i = MX_STR_POS;
        MX_STR_POS--;
        while (i > 0) {
            MX_STR[MX_STR_LEN - i - 1] = MX_STR[MX_STR_LEN - i];
            i--;
        }
        MX_STR_LEN--;
    }
    ush->input->comands[MX_MAX_COMAND][MX_STR_LEN - 1] = 0;
}
