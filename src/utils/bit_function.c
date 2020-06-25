#include "ush.h"

int mx_bit_smbl(char *str) {
    unsigned char tmp = (unsigned char)str[0];

    if (tmp >> 7 == 0)
        return 1;
    if (tmp >> 5 == 6)
        return 2;
    if (tmp >> 4 == 14)
        return 3;
    if (tmp >> 3 == 30)
        return 4;
    return 0;
}

int mx_len_smbl(int sum, char *str) {
    unsigned char tmp;
    int counter = 0;

    for (int i = 0; i < sum; i++) {
        tmp = (unsigned char)str[i];
        if (tmp >> 7 == 0)
            counter++;
        else if (tmp >> 6 == 3)
            counter++;
        if (tmp >> 3 == 30)
            counter++;
    }
    return counter;
}
