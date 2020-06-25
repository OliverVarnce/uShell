#include "ush.h"

static int mx_sum_commands(char *str, int end) {
    int sum = 0;

    for (int i = 0; i <= end; i ++) {
        if (end == 1 && str[0] == 0 && sum == 0)
            sum--;
        if (str[i] == 0 && i != 0 && i != end -1)
            sum++;
    }
    return sum;
}

static char *mx_create_command(char *str, int *position) {
    char *command = mx_strdup(str);
    int len = mx_strlen(command);

    *position = *position + len + 1;
    return command;
}

char **mx_create_commands(char *str, int end) {
    int sum = mx_sum_commands(str, end);
    char **commands = (char **) malloc (sizeof(char *) * (sum + 1));
    int position = 0;

    for (int i = 0; position < end && i < sum; i++) {
        if (str[position] == 0)
            position++;
        commands[i] = mx_create_command(&str[position], &position);
    }
    commands[sum] = 0;
    mx_strdel(&str);
    return commands;
}
