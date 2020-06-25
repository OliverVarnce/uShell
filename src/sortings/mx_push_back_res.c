#include "ush.h"

void mx_push_back_res(t_variable **list, t_variable *new) {
    if (list) {
        if (*list) {
            t_variable *current = *list;

            while(current->next != NULL) {
                current = current->next;
            }
            current->next = new;
        }
        else {
            *list = new;
        }
    }
}
