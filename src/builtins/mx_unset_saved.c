#include "ush.h"

void mx_unset_saved(int *fds, int *save, int oper) {
    dup2(save[0], 0);
    dup2(save[1], 1);
    if ((oper & OP_PIPE_W) || (oper & OP_MORE))
        close(fds[1]);
    if (oper & OP_PIPE_R)
        close(fds[0]);
    close(save[0]);
    close(save[1]);
}
