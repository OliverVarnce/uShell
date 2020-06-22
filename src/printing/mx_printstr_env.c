#include "ush.h"

void mx_printstr_env(char *str) {
    char *tmp = 0;

    tmp = mx_strdup(getenv(str));
    mx_printstr(str);
    mx_printstr("=");
    mx_printstr(tmp);
    mx_printstr("\n");
    free(tmp);
}
