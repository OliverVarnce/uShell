#include "ush.h"

void mx_del_top_process(t_ush *ush) {
    if (!ush->processes)
        return;
    mx_del_strarr(&ush->processes->name);
    mx_pop_front_proc(&ush->processes);
}
