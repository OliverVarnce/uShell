#include "ush.h"

void mx_check_outprogram_new_line(void) {
    int twidth = mx_get_twidth() - 1;
    int save_fd = dup(1);
    int term_fd = open("/dev/tty", O_WRONLY);

    dup2(term_fd, 1);
    //write(1,"%",1);
    for (int i = 0; i < twidth; i++)
        mx_printstr(" ");
    mx_printstr("\r");
    mx_print_esc("J");
    dup2(save_fd, 1);
    close(save_fd);
    close(term_fd);
}

static void print_two_str(char *str1, char *str2) {
    mx_printstr(str1);
    mx_printstr(str2);
}

void mx_terminal_out(char *name, int table2, int pos, char *str) {
    int symbol = mx_bit_sumbol(&str[table2 - pos - 1]);
    int len = (int) name[0];
    int col = mx_get_twidth();

    print_two_str(&name[1], str);
    mx_printstr(" ");
    for (int i = (mx_len_symbol(table2, str) + len) / col; i > 0; i--)
        mx_print_esc("1F");
    mx_printstr("\r");
    mx_printstr(&name[1]);
    write(1, str, table2 - pos - 1);
    if ((mx_len_symbol(table2 - pos, str) + len) % col == 0) {
        if (pos == 0)
            mx_printstr(" ");
        else
            write(1, &str[table2 - pos - 1], symbol);
        mx_printstr("\b");
    }
    mx_printstr("\x1b[0m");
}

void mx_clean_terminal(char *name, int table2, int pos, char *str) {

    int tmp;
    int len = (int)name[0];

    tmp = (mx_len_symbol(table2 - pos, str) + len) / mx_get_twidth();
    for (int i = tmp; i > 0; i--) {
        mx_print_esc("1F");
    }
    write(1,"\r",1);
    mx_print_esc("J");
}

void mx_clean_space_in_term(char *str, t_ush *ush, char *new_str) {
    int tmp;
    int col = mx_get_twidth();

    tmp = (mx_len_symbol(MX_STR_LEN - MX_STR_POS, str) + 4) / col;
    for (int i = tmp; i > 0; i--) {
        mx_print_esc("1F");
    }
    write(1,"\r",1);
    mx_print_esc("J");
    mx_printstr(MX_USH);
    mx_printstr(new_str);
}
