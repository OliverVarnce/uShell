#include "ush.h"

void mx_del_top_process(t_ush *ush) {
    if (!ush->processes)
        return;
    mx_del_strarr(&((t_process*)ush->processes->data)->name);
    mx_pop_front(&ush->processes);
}
