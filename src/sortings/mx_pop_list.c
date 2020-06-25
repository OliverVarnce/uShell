#include "ush.h"

static bool del(t_variable **head) {
    //del_data(s->data);
    mx_pop_front_free_data(head);
    return 1;
}

//void mx_pop_list(t_list **head, void *data, bool(*if_list)(void *, void *),
//                 void(*del_data)(void *)) {
//    t_list *s = NULL;
//    t_list *tmp = NULL;
//
//    if (head == 0 || *head == 0)
//        return;
//    s = *head;
//    if (if_list(data, s->data) && del(s, head, del_data))
//        return;
//    for (; s->next != 0;) {
//        if (if_list(data, s->next->data)) {
//            del_data(s->next->data);
//            tmp = s->next;
//            free(tmp->data);
//            s->next = tmp->next;
//            free(tmp);
//            return;
//        }
//        s = s->next;
//    }
//}


void mx_pop_list(t_variable **head, void *data, bool(*if_list)(void *, void *)) {
    t_variable *s = NULL;
    t_variable *tmp = NULL;

    if (head == 0 || *head == 0)
        return;
    s = *head;
    if (if_list(data, s) && del(head))
        return;
    for (; s->next != 0;) {
        if (if_list(data, s->next)) {
            if (malloc_size(s->next->name))
                mx_strdel(&(s->next->name));
            if (malloc_size(s->next->value))
                mx_strdel(&(s->next->value));
            if (malloc_size(s->next->mem))
                mx_strdel(&(s->next->mem));
//            del_data(s->next);
            tmp = s->next;
            //free(tmp->data);
            s->next = tmp->next;
            free(tmp);
            return;
        }
        s = s->next;
    }
}
