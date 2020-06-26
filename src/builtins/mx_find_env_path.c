#include "ush.h"

char *mx_find_env_path(char *s1, char *s2, int *i) {
    char *res = NULL;

    s1++;
    if (*s1 == 'i')
        for (; *s1 == 'i'; s1++);
    if (*s1 == 'P' && *(s1 + 1) != '\0') {
        s1++;
        res = mx_strdup(s1);
    }
    else {
        (*i)++;
        if (s2)
            res = mx_strdup(s2);
    }
    return res;
}
