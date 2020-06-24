#include "ush.h"

void mx_print_esc(char *s) {
    char tmp = 27;

    write(1, &tmp, 1);
    write(1, "[", 1);
    mx_printstr(s);
}
