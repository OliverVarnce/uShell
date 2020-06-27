#include "ush.h"

static void skip_spaces (char *s, int *begin, int end) {
    while (s[*begin] && *begin < end) {
        if (s[*begin] != ' ') {
            return;
        }
        (*begin)++;
    }
}

static void current_pos(int *currPos, char c, char *s) {
    if (s[*currPos] == c) {
        *currPos += 1;
        if (s[*currPos] == c) {
            *currPos += 1;
        }
    }
}

static int get_token_priority(char *s) {
    if (mx_strcmp(s, "||") == 0 || mx_strcmp(s, "&&") == 0)
        return 60;
    else if (s[0] == '|')
        return 50;
    else if (s[0] == '>')
        return 40;
    else if (s[0] == '<')
        return 30;
    else if (s[0] == '&')
        return 20;
    else
        return 10;
}

static bool send_operator(char c) {
    if (c == '|' || c == '&' || c == '>' || c == '<')
        return true;
    return false;
}

t_token* mx_find_next_tok(int *currPos, int end, char *s,
                           t_ush *processes) {
    int tokenStart = *currPos;
    t_token *newToken = 0;
    char *newValue = 0;

    if (*currPos >= end)
        return 0;
    if (mx_is_char(s[tokenStart]))
        newToken = mx_token_in_program(currPos, end, s, processes);
    else if (send_operator(s[tokenStart])) {
        newToken = mx_create_token(2,0,0);
        current_pos(currPos, s[tokenStart], s);
        newValue = mx_strndup(&s[tokenStart], *currPos - tokenStart);
        mx_add_to_str_arr(&newToken->value, newValue);
        newToken->type = mx_get_tok(newToken->value[0]);
        newToken->priority = get_token_priority(newToken->value[0]);
    }
    skip_spaces(s, currPos, end);
    return newToken;
}
