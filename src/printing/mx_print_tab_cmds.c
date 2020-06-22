#include "ush.h"

static void print_cmds(int max, char *cmds) {
    int char_cmds = mx_strlen(cmds);

    mx_printstr(cmds);
    for (int i = char_cmds; i != max; i++)
        mx_printchar(' ');
}

static int max_cmds(t_list *list_cmd) {
    t_list *cmds = list_cmd;
    int tmp = 0;
    int max = 0;

    while (cmds != 0) {
        tmp = mx_strlen(cmds->data);
        if (tmp > max)
            max = tmp;
        cmds = cmds->next;
    }
    return max;
} 

static int row_tab(int *max, t_list *list_cmd) {
    int cols = 0;
    int row = 0;
    int sum = mx_list_size(list_cmd);

    cols = mx_get_twidth() / *max;
    if (cols == 0)
        cols = 1;
    row = sum / cols;
    if (sum % cols != 0)
        row++;
    return row;
}

void mx_print_tab_cmds(t_list *list_cmd) {
    int max = max_cmds(list_cmd) + 2;
    int row = row_tab(&max, list_cmd);
    t_list *lst = NULL;
    t_list *newlst = list_cmd;
    int i[] = {0,0};

    for (i[0] = row; i[0] != 0; i[0]--) {
        lst = newlst;
        while (lst != 0) {
            print_cmds(max, lst->data);
            for (i[1] = row; lst != 0 && i[1] != 0; i[1] --)
                lst = lst->next;
        }
        mx_printstr("\n");
        newlst = newlst->next;
    }
}
