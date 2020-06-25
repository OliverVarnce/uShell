#include "ush.h"

void mx_loop(char str, t_ush *ush) {
     for (; str != 0;) {
         if (ush->history && str == 1) {
             mx_parsing(ush->history->data, ush);
             mx_check_outprogram_new_line();

         }
         if (ush->is_exit)
             break;
         str = mx_input(ush);
         ush->if_ctrl_c = 1;
         write(1, "\n", 1);
     }
}
