#include "libmx.h"

void mx_del_list(t_list **lst) {
    t_list *w = *lst;

    while (w != NULL) {
        t_list *tmp = w;
        
        w = w->next;
        free(tmp);
    }
    *lst = NULL;
}
