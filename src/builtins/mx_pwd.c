#include "ush.h"


static int flags_in_str(char *s) {
    int i = 0;
    int flags = 0;

    while (s[++i]) {
        if (s[i] == 'L') 
            flags |= 1;
        else if (s[i] == 'P') 
            flags |= 2;
        else {
            return -1;
        }
    }
    return flags;
}

static int find_flags(char **av, int *i) {
    int flag = 0;

    while (av[++(*i)]) {
        if (av[(*i)][0] != '-')
            return flag;
        int c = flags_in_str(av[*i]);
        if (c == -1) {
            return 0;
        }
        flag |= c;
    }
    i--;
    return flag;
}

int mx_pwd(char **av, t_ush *ush) {
    int i = 0;
    int flag = find_flags(av, &i);

    if (flag & 2) {
        printf("%s\n", ush->pwd_p);
    }
    else
        printf("%s\n", ush->pwd_l);
    return 0;
}
