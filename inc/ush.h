#ifndef USH_H
#define USH_H

#include <unistd.h>
#include <stdlib.h>
#include <xlocale.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <term.h>
#include <sys/types.h>
#include <regex.h> 
#include <pwd.h>
#include <stdio.h>
#include <dirent.h>
#include "libmx.h"
#include <time.h>
#include <termios.h>
#include <signal.h>
#include <sys/wait.h>
#include <termcap.h>
#include <wchar.h>
#include <sys/cdefs.h>
#include <sys/_types.h>
#include <sys/_types/_pid_t.h>
#include <sys/_types/_id_t.h>
#include <sys/signal.h>
#include <sys/resource.h>


#define MX_W_INT(w)         (*(int *)&(w))
#define MX_WST(x)           (x & 0177)
#define MX_WIFEXIT(x)       (MX_WST(x) == 0)
#define MX_WIFSIG(x)        (MX_WST(x) != _WSTOPPED && MX_WST(x) != 0)
#define MX_WTERMSIG(x)      (MX_WST(x))
#define MX_EXSTATUS(x)      ((MX_W_INT(x) >> 8) & 0x000000ff)

#define MX_FLAGS_W O_RDWR | O_CREAT | O_TRUNC, S_IWRITE | S_IREAD
#define MX_FLAGS_WE O_RDWR | O_CREAT | O_APPEND, S_IWRITE | S_IREAD
#define MAX_PROC_COUNT 500
#define MX_USH "\x4\x1b[32;5;76mu$h> \x1b[37;5;76m"
#define MX_SEARCH "Search > "
#define MX_PATH ((t_token*)tmp->next->next->data)->value[0]
#define MX_FUNC_RETURN mx_return_var("HOME", &(ush->var_tree))
#define MX_GET_PATH (argv[i] ? argv[i] : MX_FUNC_RETURN)
#define MX_REG_EXPORT   "^[A-Za-z_]+[A-Za-z_0-9]*(=.*)?$"
#define MX_REG_ERR      "^^-(i+)?[^Pui]"
#define MX_REG_I        "^-i+((P|u)?|((P|u).+)?)$"
#define MX_REG_U        "^-(i+)?u.*$"
#define MX_REG_P        "^-(i+)?P.*$"
#define MX_REG_VER      "^.+=.*$"
#define MX_REG_PROG     "^[^-]"

// VARIABLES

typedef struct s_var {
    char *name;
    char *value;
    bool flag;
    struct s_var *next;
}              t_var;

typedef struct s_variable {
    char *name;
    char *value;
    bool is_env;
    char *mem;
    struct s_variable *next;
}              t_variable;

typedef struct s_tree_node {
    struct s_tree_node *left;
    struct s_tree_node *right;
    struct s_tree_node *parent;
    void *data;
}               t_tnode;

enum e_branch {
    RIGHT,
    LEFT
};

enum e_operator_status {
    OP_NOTHING,
    OP_PIPE_R,
    OP_PIPE_W,
    OP_PIPE_RW,
    OP_MORE = 4,
    OP_DMORE = 8,
    OP_LESS = 16,
    LEFT_VISITED = 128,
    RIGHT_VISITED = 64,
    OP_AMP = 32
};

// AST
enum e_type_of_token{
    TYPE_OPERATOR,
    TYPE_COMMAND,

    TYPE_FILENAME,
    TYPE_DESC_NUMB,
};

typedef struct s_token{
    char type;
    char **value;
    int priority;
}              t_token;

typedef struct s_process {
    char **name;
    pid_t pid;
    int index;
    struct s_process *next;
}              t_process;

typedef struct s_input {
    char **comands;
    char **comand_tab;
    int id;
    int maxcmd;
    int inplen;
    int endpoint;
    int symb;
    int tabposition;
}              t_input;

typedef struct s_ush {
    struct termios term_old;
    struct termios term_new;
    char **env;
    t_list *history;
    t_input *input;
    t_process *processes;
    bool is_exit;
    bool if_ctrl_c;
    int exit_status;
    char *pwd;
    char *pwd_l;
    char *pwd_p;
    char *old_pwd;
    char *path;
    char *home;
    t_variable *var_tree;
    int last_return;
}              t_ush;

void mx_push_back_res(t_variable **list, t_variable *new);

enum e_keys{
    CTRL_A = 1,
    CTRL_W = 23,
    CTRL_E = 5,
    CTRL_R = 18,
    CTRL_T = 20,
    CTRL_Y = 25,
    CTRL_U = 21,
    CTRL_I = 9, // TAB
    CTRL_P = 16,
    CTRL_CLOSE_BRACKET = 29,
    CTRL_D = 4,
    CTRL_F = 6,
    CTRL_G = 7, // sound
    CTRL_H = 8,
    CTRL_K = 11, // vertical tab
    CTRL_L = 12, // new feed
    CTRL_Z = 26,
    CTRL_X = 24,
    CTRL_C = 3,
    CTRL_B = 2,
    CTRL_N = 14,
    KEY_ESCAPE = 27,
    KEY_SPACE = 32,
    KEY_ENTER = 13
};


// tree
void mx_insert_tree(t_tnode **root, t_tnode *new,
    int (*cmp)(void*, void*),
    void (*free_)(void *)
);


t_tnode* mx_get_1st_node(t_tnode *root);
void mx_arrstr_to_arrstr(char ***strs, char ***str);
t_tnode *mx_create_tnode(void *data);
void mx_launch_ush(t_variable **var_tree, char **env);
void mx_del_our_node(t_tnode **root, void *data, int (*cmp)(void*, void*), void (*free_tnode)(t_tnode *tnode));
void mx_filling_env(t_variable **var_tree, char *name, char *value, char *mem);
t_tnode *mx_find_our_node(t_tnode *root, void *data, int (*cmp)(void*, void*));
void mx_new_param(char *str, int *start, int end, t_ush *processes);
char *mx_return_var(char **str, t_variable **var_tree);
char *mx_return_var2(const char *str, t_variable **var_tree);
void mx_find_cur_list(t_variable **var_tree, char *name, char *value);
t_token *mx_create_token(char type, char **value, int priority);
void mx_clear_tokens(t_list **tokens);
t_token* mx_find_next_tok(int *start, int end, char *str, t_ush *processes);
char mx_get_tok(char *str);
void mx_term_param(t_ush *processes, int *i, char **new_str);
int mx_checker_flag(char *str, int *pos, int end, int flag);
void mx_read_user(char **user);
t_token *mx_token_in_program(int *curr_pos, int end, char *str, t_ush *processes);
int mx_exec_dmore(t_tnode *root, int *fds, int operatorStatus, t_ush *ush);
void mx_ush_init(t_ush **ush, char **envp);
void mx_sub_str(char **str);
void mx_parsing(char *str, t_ush *ush);
t_list *mx_lexer(char *str, t_ush *processes);
bool mx_syntax_check(t_list *tokens);
void mx_execute(char **commands, t_ush *processes);
void mx_ush_close(t_ush *ush);
void mx_charge_parametr_export(char *value, char *tmp, t_variable *data);

void mx_write_from_to(int from , int to, off_t start);
// typedef struct termios t_termios;

//BUILT IN
int mx_cd(char **argv, t_ush *ush);
int mx_history(t_list **list_comands);
void mx_printstr_env(char *str);
int mx_pwd(char **argv, t_ush *ush);
void mx_echo(char **str,  t_ush *ush);
void mx_env(char **argv, t_ush *ush);
void mx_export(char **argv, t_variable **var_tree, t_ush *ush);
void mx_unset(char **argv, t_variable **var_tree, t_ush *ush);
void mx_which(char **argv, t_ush *ush);
bool mx_is_buildin(char *str);
void mx_jobs(t_ush *ush);
void mx_fg(char **argv, t_ush *ush);
void mx_exit(t_token *token, t_ush *ush);

//CD 
int mx_chdir_p(char *path, t_ush *ush, char flags);
char* mx_add_new_path(char *path, char *new_part);
char* mx_del_last_var(char *path);
int mx_chdir_l(char *path, t_ush *ush, char flags);

// Which
bool mx_is_commad(char *fullname, int flags);

//
bool mx_check_symbol(char *str, int position, char symbol);
void mx_paste_nonascii(t_ush *ush, char *chars);
void mx_ctrl_r(t_ush *ush);
int mx_ascii(t_ush *ush, char *chars, unsigned int ch);
int mx_last_flag(char *str, int *position, int end, int flag);
char *mx_parsing_input(char *str);
char *mx_str_check(char *str, t_ush *processes, bool dqute);
char *mx_bquote_str(char **str, t_ush *processes);
char **mx_create_commands(char *str, int end);
void mx_one_symbol(char **str, char ch, int *count, int position);
void mx_is_ascii(char *chars, t_ush *ush);
int mx_bit_symbol(char *str);
int mx_len_symbol(int sum, char *str);
int mx_input(t_ush *ush);
void mx_print_esc(char *s);
void mx_check_outprogram_new_line(void);
void mx_clean_space_in_term(char *str, t_ush *ush, char *new_str);
void mx_print_esc(char *s);
void mx_terminal_stdout(char *name, int table2, int pos,char *str);
void mx_clean_terminal(char *name, int table2, int pos,char *str);
void mx_print_esc(char *s);
void mx_key_delite(t_ush *ush);
char **mx_lone_tab(char *parsing, char **str, t_ush *ush);
char *mx_mini_parser_tab(char *parsing, t_ush *ush);
void mx_read_comand(char *parsing, t_list **list_comand);
void mx_many_tabs(char **str, char **comands, t_ush *ush);
void mx_print_tab_comands(t_list *list_comand);
t_ush* mx_shell_info(t_ush *ush);
bool mx_is_link(char *file);
void mx_unset_saved(int *fds, int *savedFds, int operator_starus);
t_var *mx_var_tree_to_var(t_variable *var_tree);
int mx_twight_1();

// lexer
bool mx_is_char(char c);
void mx_home(char **str, int *i, t_ush *processes);
void mx_replace(char **str, size_t start, size_t end, char *str_new);
bool mx_is_operator(t_token *token);
unsigned int mx_read_keyboard(t_ush *ush);

// AST
t_tnode* mx_create_ast(t_list** tokens, t_tnode *prev);
void mx_delete_last(t_tnode **root);

//exec
int mx_execute_tree(t_tnode *root, int *fds, char operator_status, t_ush *ush);
int mx_exec_more(t_tnode *root, int *fds, int operator_status, t_ush *ush);
int exec_token(t_token *token, int *fds, char operator_status, t_ush *ush);
void mx_exec_less(t_tnode *root, int *fds, char operator_status, t_ush *ush);
void mx_execute_proces(t_token* token);
void mx_close_all_pr(t_ush *ush);
int mx_pipe_execute(t_tnode *root, int *fds, char operator_status, t_ush *processes);
int mx_fill_build(t_token *token, t_ush *ush);
void mx_exec_env_pr(char *path, char **argv, char **env, t_ush *ush);

// processes
int mx_add_process(t_process **processes, pid_t pid, char **name);
void mx_del_top_process(t_ush *ush);
void mx_del_pid_process(t_ush *ush, int pid);
void mx_wait_process(t_ush *ush, char **argv);
void mx_segfault_in();
void mx_loop(char str, t_ush *ush);

//print
void mx_print_susp(char **mas_name);
void mx_print_cont(char **mas_name, int pid);
char **mx_find_name(t_ush *ush, int numb);

// env 

char **mx_call_env(char **argv, int i);
char **mx_env_to_ush(t_var *var);
bool mx_find_env(char **argv, char **path, t_var *var, int *i);
bool mx_printerr_env(char *str, int flag);
void mx_print_env(t_var *var);
void mx_clear_path(t_var *var, char *path);
bool mx_reg(char *str, char *regular);
char *mx_find_env_path(char *str1, char *str2, int *i);
int mx_del_variable_env(char *str1, char *str2, t_var *var, int *i);

// echo
int mx_xo(char *str, int *i);

//utils
char *mx_str_concatenation(char *s1, char *s2);
char **mx_dupl_arr_str(char **strs);
int mx_str_diff(const char *s1, const char *s2);
char *mx_str_merge(char *s1, char *s2);
char *mx_arr_str_to_str(char **strings);
unsigned int mx_get_char();
bool mx_is_str_begin(char *string, char *start);
void mx_add_to_str_arr(char ***strings, char *str);
void mx_pop_front_free_data(t_variable **head);
void mx_pop_front_free_data_list(t_list **head);
//void mx_pop_front_free_data(t_list **head);
//void mx_pop_list(t_variable **head, void *data, bool(*if_list)(void *, void *),
//                 void(*del_data)(void *));
void mx_pop_list(t_variable **head, void *data, bool(*if_list)(void *, void *));
void mx_push_front_proc(t_process **list, t_process *new_head);
#endif
