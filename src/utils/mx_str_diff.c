#include "ush.h"

int mx_str_diff(const char *s1, const char *s2) {
    for (int i = 0; s2[i]; i++) {
        if (s1[i] < s2[i] || s1[i] > s2[i])
            return s1[i] - s2[i];
    }
    return 0;
}
