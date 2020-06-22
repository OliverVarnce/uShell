#include "ush.h"

static void print_row(t_list *tmp, char c) {
    char *name = mx_arrstr_to_str(((t_processes*)tmp->data)->name);

    printf("[%d] %c suspended %s\n", ((t_processes*)tmp->data)->index, c,
        name);
    free(name);
}

void mx_jobs(t_ush *ush) {
    t_list *tmp = ush->processes;
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
    ush->last_return = 0;
}
