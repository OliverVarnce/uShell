#include "ush.h"

static void print_row(t_process *tmp, char c) {
    char *name = mx_arr_to_str(tmp->name);

    printf("[%d] %c suspended %s\n", tmp->index, c, name);
    free(name);
}

void mx_jobs(t_ush *ush) {
    t_process *tmp = ush->processes;
    char c = 0;
    int i = -1;

    if (tmp == 0)
        printf("fg: no current job\n");
    while (tmp) {
        
        if (++i == 0)
            c = '+';
        else if (i == 1)
            c = '-';
        else 
            c = ' ';
        print_row(tmp, c);
        tmp = tmp->next;
    }
    ush->last_status = 0;
}
