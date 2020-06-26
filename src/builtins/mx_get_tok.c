#include "ush.h"

static bool logic_comand(char c) {
    if ((c == '|') || (c == '&') || (c == '>') || (c == '<')
        || (c == '\n') || (c == ';') || (c == '\0'))
        return false;
    return true;  
}

char mx_get_tok(char *str) {
    if (str == 0)
        return 2;
    if (str[0] == 0)
        return 2;
    if (logic_comand(str[0]))
        return TYPE_COMMAND;
    return TYPE_OPERATOR;
}
