#include "ush.h"

static void buildin_list_1(t_token *token, t_ush *ush) {
    if (mx_strcmp(token->value[0], "cd") == 0) 
        ush->last_return = mx_cd(token->value, ush);
    else if (mx_strcmp(token->value[0], "history") == 0) 
        ush->last_return = mx_history(&(ush->history));
    else if (mx_strcmp(token->value[0], "pwd") == 0) 
        ush->last_return = mx_pwd(token->value, ush);
    else if (mx_strcmp(token->value[0], "echo") == 0) 
        mx_echo(token->value, ush);
    else if (mx_strcmp(token->value[0], "exit") == 0)
        mx_exit(token, ush);
    else if (mx_strcmp(token->value[0], "fg") == 0)
        mx_fg(token->value, ush);
}

static void buildin_list_2(t_token *token, t_ush *ush) {
    if (mx_strcmp(token->value[0], "export") == 0)
        mx_export(token->value, &(ush->environ), ush);
    else if (mx_strcmp(token->value[0], "unset") == 0)
        mx_unset(token->value, &(ush->environ), ush);
    else if (mx_strcmp(token->value[0], "stop") == 0)
        mx_close_all_pr(ush);
    else if (mx_strcmp(token->value[0], "env") == 0)
        mx_env(token->value, ush);
    else if (mx_strcmp(token->value[0], "which") == 0)
        mx_which(token->value, ush);
    else if (mx_strcmp(token->value[0], "jobs") == 0)
        mx_jobs(ush);
}

int mx_buildin_list(t_token *token, t_ush *ush) {
    buildin_list_1(token, ush);
    buildin_list_2(token, ush);
    return ush->exit_status;
}
