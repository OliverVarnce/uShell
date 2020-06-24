#include "libmx.h"

int mx_count_digits(long nb) {
    int len = 1;
    int sign = 0;

    if (nb < 0) {
        sign = 1;
        nb = -nb;
    }
    while (nb / 10) {
        len++;
        nb /= 10;
    }
    if (sign)
        len++;
    return len;
}

char *mx_itoa(int number) {
    char *str;
    long nb = number;
    int len = mx_count_digits(nb);
    if (nb < 0)
        nb = -nb;
    str = mx_strnew(len);
    while(len--) {
        str[len] = nb % 10 + 48;
        nb /= 10;
    }
    if (number < 0)
        str[0] = '-';
    return str;
}
