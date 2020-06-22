#include "ush.h"

static char **create_cmds(t_list **list_cmds) {
    int sum_comand = mx_list_size(*list_cmds) + 2;
    char **cmds = (char **) malloc(sum_comand * sizeof(char *));
    t_list *list = *list_cmds;

    cmds[0] = NULL;
    for (int i = 0; list != 0; i++) {
        cmds[i] = mx_strdup(list->data);
        list = list->next;
        cmds[i + 1] = NULL;
    }
    return cmds;
}

int mx_history(t_list **list_cmds) {
    char **cmds = create_cmds(list_cmds);

    for (int i = 1; cmds && cmds[i - 1]; i++) {
        if (i < 10)
            mx_printstr("  ");
        else if (i < 100)
            mx_printstr(" ");
        mx_printint(i);
        mx_printstr("  ");
        mx_printstr(cmds[i - 1]);
        mx_printstr("\n");
    }
    mx_del_strarr(&cmds);
    return 0;
}
