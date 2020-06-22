#include "ush.h"


static int flag_from_cmd(char *str) {
    int i = 0;
    int flags = 0;

    while (str[++i]) {
        if (str[i] == 'L') 
            flags |= 1;
        else if (str[i] == 'P') 
            flags |= 2;
        else {
            return -1;
        }
    }
    return flags;
}
/* 
* 1-st bit -> -L
* 2-nd bit -> -P
*/
static int check_flag(char **argv, int *i) {
    int flags = 0;

    while (argv[++(*i)]) {
        if (argv[(*i)][0] != '-')
            return flags;
        int curr = flag_from_cmd(argv[*i]);
        if (curr == -1) {
            return 0;
        }
        flags |= curr;
    }
    i--;
    return flags;
}

int mx_pwd(char **argv, t_ush *ush) {
    int i = 0;
    int flags = check_flag(argv, &i);

    if (flags & 2) {
        printf("%s\n", ush->pwd_p);
    }
    else
        printf("%s\n", ush->pwd_l);
    return 0;
}
