APP_NAME = ush

LIBMXF = libmx

LIB_NAME = libmx.a

INC = inc/ \
	  libmx/inc/

SRC_DIR = src

OBJ_DIR = obj

SRC = $(addprefix $(SRC_DIR)/,\
		builtins/mx_add_one_rank.c \
        builtins/mx_add_process.c \
        builtins/mx_buildin_list.c \
        builtins/mx_call_vlad.c \
        builtins/mx_cd.c \
        builtins/mx_check_env.c \
        builtins/mx_close_all_pr.c \
        builtins/mx_ctrl_v_and_not_ascii.c \
        builtins/mx_del_last_rank.c \
        builtins/mx_del_pid_process.c \
        builtins/mx_del_top_process.c \
        builtins/mx_delete_tnode.c \
        builtins/mx_delete_veriable_env.c \
        builtins/mx_echo.c \
        builtins/mx_end_flag.c \
        builtins/mx_env.c \
        builtins/mx_env_to_vlad.c \
        builtins/mx_export.c \
        builtins/mx_fg.c \
        builtins/mx_find_tnode.c \
        builtins/mx_flang_comand.c \
        builtins/mx_fre_env_path.c \
        builtins/mx_get_info.c \
        builtins/mx_get_min_tnode.c \
        builtins/mx_get_name.c \
        builtins/mx_get_next_token.c \
        builtins/mx_get_path_env.c \
        builtins/mx_get_token_type.c \
        builtins/mx_get_twidth.c \
        builtins/mx_if_new_parameter.c \
        builtins/mx_jobs.c \
        builtins/mx_key_duble_tab.c \
        builtins/mx_key_tab.c \
        builtins/mx_push_env.c \
        builtins/mx_pwd.c \
        builtins/mx_read_comand.c \
        builtins/mx_return_value.c \
        builtins/mx_serch_list.c \
        builtins/mx_unset.c \
        builtins/mx_unset_fds.c \
        builtins/mx_which.c \
		exec/mx_ctrl_r.c \
		exec/mx_exec_dmore.c \
		exec/mx_exec_env_pr.c \
		exec/mx_exec_less.c \
		exec/mx_exec_more.c \
		exec/mx_exec_token.c \
		exec/mx_execute.c \
		exec/mx_execute_proces.c \
		exec/mx_execute_tree.c \
		exec/mx_pipe_execute.c \
		exec/mx_read_keyboard.c \
		exec/mx_signals.c \
		memory/mx_charge_paranetr_export.c \
		memory/mx_clear_tokens.c \
		parsers/mx_check_symbol.c \
		parsers/mx_is_buildin.c \
		parsers/mx_is_char.c \
		parsers/mx_is_commad.c \
		parsers/mx_is_link.c \
		parsers/mx_is_operator.c \
		parsers/mx_key_delite.c \
		parsers/mx_mini_parser_tab.c \
		parsers/mx_one_symbol.c \
		parsers/mx_parsing.c \
		parsers/mx_parsing_input.c \
		printing/mx_print_cont.c \
		printing/mx_print_env.c \
		printing/mx_print_error_env.c \
		printing/mx_print_esc.c \
		printing/mx_print_susp.c \
		printing/mx_print_tab_comands.c \
		printing/mx_printstr_env.c \
		utils/main.c \
		utils/bit_function.c \
        utils/main.c \
        utils/mx_0_and_x.c \
        utils/mx_arrstr_to_str.c \
        utils/mx_ascii.c \
        utils/mx_audit_str.c \
        utils/mx_chdir_l.c \
        utils/mx_chdir_p.c \
        utils/mx_create_ast.c \
        utils/mx_create_comands.c \
        utils/mx_create_tnode.c \
        utils/mx_create_token.c \
        utils/mx_delete_ast.c \
        utils/mx_do_replace.c \
        utils/mx_dupstrarr.c \
        utils/mx_exit.c \
        utils/mx_history.c \
        utils/mx_home.c \
        utils/mx_input.c \
        utils/mx_insert_tree.c \
        utils/mx_is_str_starts.c \
        utils/mx_lexer.c \
        utils/mx_not_ascii.c \
        utils/mx_parametr_shell.c \
        utils/mx_reg.c \
        utils/mx_start_program.c \
        utils/mx_str_bquote.c \
        utils/mx_strarr_add_to_strarr.c \
        utils/mx_strcmp2.c \
        utils/mx_strjoin2.c \
        utils/mx_strjoin3.c \
        utils/mx_subs.c \
        utils/mx_syntax_analyzer.c \
        utils/mx_token_in_program.c \
        utils/mx_ush_close.c \
        utils/mx_ush_init.c \
        utils/mx_var_tree_to_var.c \
        utils/mx_wait_process.c \
        utils/mx_write_from_to.c \
        utils/mx_getchar.c \
        utils/out_monitor.c \
        utils/mx_add_to_strarr.c \
        utils/mx_pop_front_free_data.c \
        utils/mx_pop_list.c)



OBJ =	mx_add_one_rank.o \
        mx_add_process.o \
        mx_buildin_list.o \
        mx_call_vlad.o \
        mx_cd.o \
        mx_check_env.o \
        mx_close_all_pr.o \
        mx_ctrl_v_and_not_ascii.o \
        mx_del_last_rank.o \
        mx_del_pid_process.o \
        mx_del_top_process.o \
        mx_delete_tnode.o \
        mx_delete_veriable_env.o \
        mx_echo.o \
        mx_end_flag.o \
        mx_env.o \
        mx_env_to_vlad.o \
        mx_export.o \
        mx_fg.o \
        mx_find_tnode.o \
        mx_flang_comand.o \
        mx_fre_env_path.o \
        mx_get_info.o \
        mx_get_min_tnode.o \
        mx_get_name.o \
        mx_get_next_token.o \
        mx_get_path_env.o \
        mx_get_token_type.o \
        mx_get_twidth.o \
        mx_if_new_parameter.o \
        mx_jobs.o \
        mx_key_duble_tab.o \
        mx_key_tab.o \
        mx_push_env.o \
        mx_pwd.o \
        mx_read_comand.o \
        mx_return_value.o \
        mx_serch_list.o \
        mx_unset.o \
        mx_unset_fds.o \
        mx_which.o \
  		mx_ctrl_r.o \
  		mx_exec_dmore.o \
  		mx_exec_env_pr.o \
  		mx_exec_less.o \
  		mx_exec_more.o \
  		mx_exec_token.o \
  		mx_execute.o \
  		mx_execute_proces.o \
  		mx_execute_tree.o \
  		mx_pipe_execute.o \
  		mx_read_keyboard.o \
  		mx_signals.o \
  		mx_charge_paranetr_export.o \
  		mx_clear_tokens.o \
  		mx_check_symbol.o \
  		mx_is_buildin.o \
  		mx_is_char.o \
  		mx_is_commad.o \
  		mx_is_link.o \
  		mx_is_operator.o \
  		mx_key_delite.o \
  		mx_mini_parser_tab.o \
  		mx_one_symbol.o \
  		mx_parsing.o \
  		mx_parsing_input.o \
  		mx_print_cont.o \
  		mx_print_env.o \
  		mx_print_error_env.o \
  		mx_print_esc.o \
  		mx_print_susp.o \
  		mx_print_tab_comands.o \
  		mx_printstr_env.o \
  		main.o \
  		bit_function.o \
        mx_0_and_x.o \
        mx_arrstr_to_str.o \
        mx_ascii.o \
        mx_audit_str.o \
        mx_chdir_l.o \
        mx_chdir_p.o \
        mx_create_ast.o \
        mx_create_comands.o \
        mx_create_tnode.o \
        mx_create_token.o \
        mx_delete_ast.o \
        mx_do_replace.o \
        mx_dupstrarr.o \
        mx_exit.o \
        mx_history.o \
        mx_home.o \
        mx_input.o \
        mx_insert_tree.o \
        mx_is_str_starts.o \
        mx_lexer.o \
        mx_not_ascii.o \
        mx_parametr_shell.o \
        mx_reg.o \
        mx_start_program.o \
        mx_str_bquote.o \
        mx_strarr_add_to_strarr.o \
        mx_strcmp2.o \
        mx_strjoin2.o \
        mx_strjoin3.o \
        mx_subs.o \
        mx_syntax_analyzer.o \
        mx_token_in_program.o \
        mx_ush_close.o \
        mx_ush_init.o \
        mx_var_tree_to_var.o \
        mx_wait_process.o \
        mx_write_from_to.o \
        mx_getchar.o \
        out_monitor.o \
        mx_add_to_strarr.o \
        mx_pop_front_free_data.o \
        mx_pop_list.o

CC = clang

CFLAGS = -std=c11 -Wall -Wextra -Werror -Wpedantic #-g3 -fsanitize=address

all : install

install : libmx/libmx.a ush

libmx/libmx.a:
	@make -C $(LIBMXF)

ush : $(SRC) inc/ush.h libmx/libmx.a
	@$(CC) $(CFLAGS) -c $(SRC) $(foreach d, $(INC), -I $d)
	@$(CC) -ltermcap $(CFLAGS) $(OBJ) $(LIBMXF)/$(LIB_NAME) -o $(APP_NAME)
	@printf "\r\33[2K$@ \033[32;1mcreated\033[0m\n"
	@mkdir -p $(OBJ_DIR)
	@mv $(OBJ) $(OBJ_DIR)
	@printf "$(NAME) \033[31;1minstalled\033[0m\n"

uninstall : clean
	@make uninstall -C $(LIBMXF)
	@rm -rf $(APP_NAME) $(OBJ)
	@printf "$(NAME) \033[31;1muninstalled\033[0m\n"

clean :
	@make clean -C $(LIBMXF)
	@rm -rf $(OBJ_DIR)
	@printf "$(OBJD)\t   \033[31;1mdeleted\033[0m\n"

reinstall : uninstall install