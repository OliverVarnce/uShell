#include "ush.h"

void mx_print_susp(char **mas_name) {
    char *name = mx_arr_str_to_str(mas_name);

    printf("\nush: suspended %s\n", name);
    free(name);
}
