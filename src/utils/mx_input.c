#include "ush.h"

static char **creat_commands(t_list **list_commands) {
    int sum_command = mx_list_size(*list_commands) + 2;
    char **commands = (char **) malloc(sum_command * sizeof(char *));
    t_list *list = *list_commands;

    commands[0] = mx_strnew(0);
    commands[1] = NULL;
    for (int i = 1; list != 0; i++) {
        commands[i] = mx_strdup(list->data);
        list = list->next;
        commands[i + 1] = NULL;
    }
    return commands;
}

static t_input *create_input(t_ush *ush) {
    t_input *input = (t_input *) malloc(sizeof(t_input));

    input->comands = creat_commands(&(ush->history));
    input->id = 0;
    input->maxcmd = mx_list_size(ush->history);
    input->inplen = 1;
    input->tabposition = 0;
    input->endpoint = 0;
    input->symb = 0;
    return input;
}

static void del_input(t_ush *ush) {
    t_input *input = ush->input;

    mx_del_strarr(&(input->comands));
    free(input);
    ush->input = 0;
}

static void return_descriptors(int fd1, int fd2, t_ush *ush) {
    del_input(ush);
    dup2(fd1, 1);
    close(fd1);
    close(fd2);
}

int mx_input(t_ush *ush) {
    unsigned int ch = 0;
    char *chars = (char*)(&ch);
    int if_next = 3;
    int save_fd1 = dup(1);
    int term_fd1 = open("/dev/tty", O_WRONLY);

    dup2(term_fd1, 1);
    ush->input = create_input(ush);
    while (if_next == 3) {
        if (chars[2] != 10 || chars[0] == 9 || chars[0] == 18)
            mx_terminal_out(MX_USH, ush->input->inplen, ush->input->endpoint,
                    ush->input->comands[ush->input->id]);
        ch = mx_read_keyboard(ush);
        if (ch > 127)
            mx_ctrl_v_and_not_ascii(ush, chars);
        else
            if_next = mx_ascii(ush, chars, ch);
        ush->input->symb = chars[0];
    }
    return_descriptors(save_fd1, term_fd1, ush);
    return if_next;
}
