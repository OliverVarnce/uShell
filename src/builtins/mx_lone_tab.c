#include "ush.h"

static bool cmp_str_level(void *s1, void *s2) {
    if (mx_strcmp(s1, s2) > 0)
        return 1;
    else 
        return 0;
}

static char **many_av_in_lst(char *path, char **s, t_ush *ush,
                                  t_list *list_comand) {
    int number_comand = 0;
    char **creat_list_comands = NULL;
    int tmp = 0;
    int size_list = mx_list_size(list_comand) + 1;
    char *name_comand = 0;

    mx_clean_space_in_term("", ush, *s);
    mx_print_tab_comands(list_comand);
    creat_list_comands = (char **)malloc(size_list * sizeof(char *));
    for (tmp = mx_strlen(path) - 1; tmp != 0 && path[tmp] != '/'; tmp--);
    tmp = mx_strlen(&path[tmp]);
    while (list_comand) {
        name_comand = list_comand->data;
        creat_list_comands[number_comand++] = mx_strdup(&name_comand[tmp - 1]);
        mx_pop_front(&list_comand);
    }
    creat_list_comands[number_comand++] = NULL;
    return creat_list_comands;
}

static void one_av_in_list(t_ush *ush, t_list *list_comand, char **s,
                               char *path) {
    int len = mx_strlen(path) - 1;

    for (; len != 0 && path[len] != '/';)
        len--;
        len = mx_strlen(&path[len]);
        path = list_comand->data;
        for (int i = len - 1; path[i]; i++)
            mx_one_symbol(s, path[i], &(ush->input->inplen), ush->input->endpoint);
        if (ush->input->endpoint != 0) {
            mx_one_symbol(s, ' ', &(ush->input->inplen), ush->input->endpoint);
            (ush->input->endpoint)++;
        }
        mx_pop_front_free_data_list(&list_comand);
}

char **mx_lone_tab(char *pars, char **s, t_ush *ush) {
    char *path = mx_mini_parser_tab(pars, ush);
    t_list *list_comand = 0;
    char **creat_list_comand = NULL;
    int comand_len = 0;

    mx_read_comand(path, &list_comand);
    list_comand = mx_sort_list(list_comand, &cmp_str_level);
    if (!((comand_len = mx_list_size(list_comand)) == 0 || comand_len == 1))
        creat_list_comand = many_av_in_lst(path, s, ush, list_comand);
    else if (comand_len == 1)
        one_av_in_list(ush, list_comand, s, path);
    else
        write(1,"\a", 1);
    mx_strdel(&path);
    mx_strdel(&pars);
    return creat_list_comand;
}
