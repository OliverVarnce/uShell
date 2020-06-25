#include "ush.h"

int mx_twight_1() {
    if (tgetent(NULL, "xterm-256color") < 0) {
        fprintf(stderr, "ush: Could not access the termcap data base.\n");
        exit(1);
    }
    return tgetnum("co");
}
