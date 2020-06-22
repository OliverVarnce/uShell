#include "ush.h"

void mx_exit(t_token *token, t_ush *ush) {
    int s = 0;

    if (token->value[1]) {
        s = atoi(token->value[1]);
        ush->exit_status = s;
    }
    else
        ush->exit_status = 0;
    ush->is_exit = true;
}
