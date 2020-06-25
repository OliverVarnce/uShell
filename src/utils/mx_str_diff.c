#include "ush.h"

char *mx_str_diff(char *s1, char *s2) {
    char *newStr = NULL;

    newStr = mx_strjoin(s1,s2);
    free(s1);
    free(s2);
    return newStr;
}
