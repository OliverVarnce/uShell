#include "ush.h"

void mx_print_stat(char **mas_name, int index, int event) {
    char *name = mx_arrstr_to_str(mas_name);

    if (event == 1)
        printf("\n[%d]  + continued %s\n",index, name);
    else if (event == 0)
        printf("\nush: suspended %s\n", name);
    free(name);
}
