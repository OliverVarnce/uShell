#include "libmx.h"

bool mx_is_str_begin(char *string, char *start) {
    if (mx_strncmp(string, start, mx_strlen(start)) == 0)
        return true;
    return false;
}
