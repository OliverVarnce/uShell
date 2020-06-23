#include "ush.h"

static int echo_flag1(char *s, int *i) {
    if (s[0] == '\\' && s[1] == 'a' && ++(*i) > 0)
        return '\a';
    else if (s[0] == '\\' && s[1] == 'b' && ++(*i) > 0)
        return '\b';
    else if (s[0] == '\\' && s[1] == 't' && ++(*i) > 0)
        return '\t';
    else if (s[0] == '\\' && s[1] == 'n' && ++(*i) > 0)
        return '\n';
    else if (s[0] == '\\' && s[1] == 'v' && ++(*i) > 0)
        return '\v';
    else if (s[0] == '\\' && s[1] == 'f' && ++(*i) > 0)
        return '\f';
    else if (s[0] == '\\' && s[1] == 'r' && ++(*i) > 0)
        return '\r';
    else if (s[0] == '\\' && s[1] == 'e' && ++(*i) > 0)
        return '\033';
    return -1;
}

static int echo_flag2(char *s) {
    char tmp;

    for (int i = 0; s[i] != '\0'; i++) {
        if (s[i] == '\\'
            && mx_reg(s + i + 1, "^(x[0-9a-fA-F]{2}.*)|(0[0-7]{2,3}.*)$")) {
            tmp = mx_0_and_x(s, &i);
        }
        else if(s[i] == '\\' && s[i + 1] == '\\')
            tmp = '\\';
        else if (s[i] == '\\' && s[i + 1] == '0' && ++i > 0)
            tmp = '\0';
        else if ((tmp = echo_flag1(&s[i], &i)) != -1);
        else if (s[i] == '\\' && s[i + 1] == 'c' && ++i > 0)
            return 0;
        else
            tmp = s[i];
        write(1, &tmp, 1);
    }
    return 1;
}

static char *switch_flags(char **s, int *count) {
    char *flag = mx_strnew(2);

    flag[0] = '0';
    flag[1] = 'e';
    for (int i = 1; s[i]; i++) {
        if (s[i][0] != '-')
            return flag;
        for (int n = 1; s[i][n] != '\0'; n++)
            if (s[i][n] != 'n' && s[i][n] != 'e' && s[i][n] != 'E')
                return flag;
        *count = i;
        for (int n = 1; s[i][n]; n++) {
            if (s[i][n] == 'n')
                flag[0] = 'n';
            else
                flag[1] = s[i][n] == 'e' ? 'e' : 'E';
        }
    }
    return flag;
}

static void error_help(int i, char *flag, char **s) {
    int err = 1;

    for (i = i + 1; s[i]; i++) {
        err = echo_flag2(s[i]);
        if (s[i + 1] && err)
            write(1, " ", 1);
    }
    if (flag[0] != 'n' && err)
        write(1, "\n", 1);
}

void mx_echo(char **s, t_ush *ush) {
    int i = 0;
    char *flag = switch_flags(s, &i);

    if (flag[1] == 'E') {
        for (i = i + 1; s[i]; i++) {
            write(1, s[i], mx_strlen(s[i]));
            if (s[i + 1])
                write(1, " ", 1);
        }
        if (flag[0] != 'n')
            write(1, "\n", 1);
    }
    else {
        error_help(i, flag, s);
    }
    ush->last_status = 0;
    free(flag);
}





