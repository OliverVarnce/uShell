#include "ush.h"

void mx_print_cont(char **mas_name, int index) {
    char *name = mx_arr_to_str(mas_name);

    printf("[%d] + continued %s\n",index, name);
    free(name);
}
