#include "libmx.h"

void mx_del_list(t_list **lst) {
    t_list *w = *lst;

    while (w != NULL) {
<<<<<<< HEAD
        t_list *tmp = w;
        
        w = w->next;
        free(tmp);
=======
        t_list *temp = w;
        
        w = w->next;
        free(temp);
>>>>>>> master
    }
    *lst = NULL;
}
