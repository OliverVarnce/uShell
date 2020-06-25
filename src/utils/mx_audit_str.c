#include "ush.h"


static void substitution_command(char **str, char **str2, t_ush *processes) {
    mx_strdel(str);
    for (int i = 0; str2[0][i]; i++) { 
        if (str2[0][i] == '\\' && (str2[0][i + 1] == '`'
            || str2[0][i + 1] == '\\')) {
            mx_replace(str2, i, i + 1, 0);
        }
    }
    *str2 = mx_str_bquote(str2, processes);
    *str = *str2;
}

static void editor_str(char **str, t_ush *processes) {
    char *tmp = 0;
    char *temp2 = 0;
    int i = 1;

    if (str[0][0] == '$')
        i++;
    tmp = mx_strndup(&str[0][i], mx_strlen(*str) - i - 1);
    if (str[0][0] == 39) {
        mx_strdel(str);
        *str = tmp;
    }
    else if (str[0][0] == 96 || str[0][0] == '$')
        substitution_command(str, &tmp, processes);
    else if (str[0][0] == 34) { 
        temp2 = mx_audit_str(tmp, processes, 1);
        mx_subs(&temp2);
        mx_strdel(str);
        mx_strdel(&tmp);
        *str = temp2;
    }
}

static bool chek_command(char *new_str, int i) {
    if (new_str[i] == 34 || new_str[i] == 39 || new_str[i] == 96) {
        if (i == 0 || new_str[i - 1] != '\''
            || !mx_check_symbol(new_str, i, new_str[i]))
            return true;
        else
            return false;
    }
    else if (new_str[i + 1] == '(' && new_str[i] == '$'
             && (i == 0 || new_str[i - 1] != '\''))
        return true;
    else if (new_str[i + 1] == '(' && new_str[i - 1] == '\''
             && !mx_check_symbol(new_str, i, '$'))
        return true;
    else
        return false;
}

static void spec_symbol(t_ush *processes, int *i, char **new_str) {
    int flag = new_str[0][*i];
    int pos = *i + 1;
    char *command = 0;

    if (new_str[0][i[0]] == '$') {
        pos++;
        flag = ')';
    }
    mx_last_flag(new_str[0], &pos, strlen(new_str[0]), flag);
    command = mx_strndup(&new_str[0][i[0]], pos - i[0]);
    editor_str(&command, processes);
    mx_replace(new_str, i[0], pos, command);
    if (command) {
        (i[0]) += mx_strlen(command);
        mx_strdel(&command);
    }
    (i[0])--;
}

char *mx_audit_str(char *str, t_ush *ush, bool dqute) {
    char *new_str = 0;
    int i = 0;
    int pos = 0;

    if (str == 0)
        return 0;
    new_str = mx_strdup(str);
    for (; new_str && new_str[i] && ush->if_ctrl_c; i++) {
        pos = i;
        if (new_str[i] == '~' && !dqute)
            mx_home(&new_str, &i, ush);
        else if (chek_command(new_str, i))
            spec_symbol(ush, &i, &new_str);
        else if (mx_check_symbol(new_str, i ,'$'))
            mx_parametr_shell(ush, &i, &new_str);
        else if (new_str[i] == '\\'
                 && (!dqute || (dqute && (new_str[i + 1] == '\\'))))
            mx_replace(&new_str, i, i + 1, 0);
    }
    return new_str;
}
