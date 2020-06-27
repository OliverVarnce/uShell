#include "ush.h"

static char **mx_commands_create(t_list **list_commands) {
    int sum_command = mx_list_size(*list_commands) + 2;
    char **commands = (char **) malloc(sum_command * sizeof(char *));
    t_list *list = *list_commands;

    commands[0] = NULL;
    for (int i = 0; list != 0; i++) {
        commands[i] = mx_strdup(list->data);
        list = list->next;
        commands[i + 1] = NULL;
    }
    return commands;
}

int mx_history(t_list **list_commands) {
    char **commands = mx_commands_create(list_commands);

    for (int i = 1; commands && commands[i - 1]; i++) {
        if (i < 10)
            mx_printstr("  ");
        else if (i < 100)
            mx_printstr(" ");
        mx_printint(i);
        mx_printstr("  ");
        mx_printstr(commands[i - 1]);
        mx_printstr("\n");
    }
    mx_del_strarr(&commands);
    return 0;
}
