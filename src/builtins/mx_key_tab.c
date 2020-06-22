#include "ush.h"

static bool cmp_str_min_max(void *str1, void *str2) {
    if (mx_strcmp(str1, str2) > 0)
        return 1;
    else 
        return 0;
}

static char **many_comand_in_list(char *path, char **str, t_ush *ush,
                                  t_list *list_cmd) {
    int number_comand = 0;
    char **creat_list_cmds = NULL;
    int tmp = 0;
    int size_list = mx_list_size(list_cmd) + 1;
    char *name_comand = 0;

    mx_clean_space_in_term("", ush, *str);
    mx_print_tab_cmds(list_cmd);
    creat_list_cmds = (char **)malloc(size_list * sizeof(char *));
    for (tmp = mx_strlen(path) - 1; tmp != 0 && path[tmp] != '/'; tmp--);
    tmp = mx_strlen(&path[tmp]);
    while (list_cmd) {
        name_comand = list_cmd->data;
        creat_list_cmds[number_comand++] = mx_strdup(&name_comand[tmp - 1]);
        mx_pop_front(&list_cmd);
    }
    creat_list_cmds[number_comand++] = NULL;
    return creat_list_cmds;
}

static void one_comand_in_list(t_ush *ush, t_list *list_cmd, char **str,
                               char *path) {
    int len_comand = mx_strlen(path) - 1;

    for (; len_comand != 0 && path[len_comand] != '/';)
        len_comand--;
        len_comand = mx_strlen(&path[len_comand]);
        path = list_cmd->data;
        for (int i = len_comand - 1; path[i]; i++)
            mx_one_symbol(str, path[i], &(ush->input->inplen), ush->input->endpoint);
        if (ush->input->endpoint != 0) {
            mx_one_symbol(str, ' ', &(ush->input->inplen), ush->input->endpoint);
            (ush->input->endpoint)++;
        }
        mx_pop_front_free_data(&list_cmd);
}

char **mx_key_tab(char *parsing, char **str, t_ush *ush) {
    char *path = mx_mini_parser_tab(parsing, ush);
    t_list *list_cmd = 0;
    char **creat_list_cmd = NULL;
    int comand_len = 0;

    mx_read_comand(path, &list_cmd);
    list_cmd = mx_sort_list(list_cmd, &cmp_str_min_max);
    if (!((comand_len = mx_list_size(list_cmd)) == 0 || comand_len == 1))
        creat_list_cmd = many_comand_in_list(path, str, ush, list_cmd);
    else if (comand_len == 1)
        one_comand_in_list(ush, list_cmd, str, path);
    else
        write(1,"\a", 1);
    mx_strdel(&path);
    mx_strdel(&parsing);
    return creat_list_cmd;
}
