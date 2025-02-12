#include "ush.h"

static int get_start_index(char *str) {
    int i = 0;

    while(str[i]) {
        if (str[i] != ' ') {
            return i;
        }
        i++;
    }
    return i;
}

static int pos_parametr(char *str, int *start) {
    int i = *start;

    while (str[i] != '=') {
        i++;
    }
    if (str[i] == '=') {
        return i;
    }
    else 
        return 0;
}

static void create_parameter(char *str, int *start, int end, t_ush *processes) {
    int pos = pos_parametr(str, start);
    char *name = mx_strndup(&str[*start], pos - *start);
    char *value = NULL;
    char *tmp = NULL;

    *start = ++pos;
    mx_last_flag(str, &pos, end, ' ');
    tmp = mx_strndup(&str[*start], pos - *start);
    *start = pos;
    value = mx_str_check(tmp, processes, 0);
    mx_strdel(&tmp);
    mx_sub_str(&value);
    mx_find_cur_list(&(processes->var_tree), name, value);
    pos = get_start_index(&str[*start]);
    if (pos != -1) 
        *start += pos;
    mx_new_param(str, start, end, processes);
}

static bool is_operator1(char c) {
    if (c == '|' || c == '&' || c == '>' || c == '<'|| c == '$' || c == ' ')
        return false;
    if (c == '='|| c == 92 || c == 34 || c == 39 || c== 96 || c == 0)
        return false;
    return true;
}

void mx_new_param(char *str, int *start, int end, t_ush *processes) {
    int check_start = *start;

    while (is_operator1(str[check_start]))
        check_start++;
    if (str[check_start] == '=') {
        create_parameter(str, start, end, processes);
    }
}

