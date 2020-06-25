#include "ush.h"

void mx_pop_front_free_data(t_variable **head) {
    t_variable *s = NULL;
    t_variable *t = NULL;

    if (head && *head)
        s = *head;
    if (s != 0) {
        s = s->next;
        t = *head;
        if (malloc_size(s->name))
            mx_strdel(&(s->name));
        if (malloc_size(s->value))
            mx_strdel(&(s->value));
        if (malloc_size(s->mem))
            mx_strdel(&(s->mem));
//        if (t->data != 0)
//            free(t->data);
//        t->data = NULL;

        t->next = NULL;
        free(t);
        *head = s;
    }
}

void mx_pop_front_free_data_list(t_list **head) {
    t_list *s = NULL;
    t_list *t = NULL;

    if (head && *head)
        s = *head;
    if (s != 0) {
        s = s->next;
        t = *head;
        if (t->data != 0)
            free(t->data);
        t->data = NULL;

        t->next = NULL;
        free(t);
        *head = s;
    }
}
