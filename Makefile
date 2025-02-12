APP_NAME = ush

LIBMXF = libmx

LIB_NAME = libmx.a

INC = inc/ \
	  libmx/inc/

SRC_DIR = src

OBJ_DIR = obj

SRC = $(addprefix $(SRC_DIR)/,\
		builtins/mx_add_new_path.c \
        builtins/mx_add_process.c \
        builtins/mx_fill_build.c \
        builtins/mx_call_env.c \
        builtins/mx_cd.c \
        builtins/mx_find_env.c \
        builtins/mx_close_all_pr.c \
        builtins/mx_paste_nonascii.c \
        builtins/mx_del_last_var.c \
        builtins/mx_del_pid_process.c \
        builtins/mx_del_top_process.c \
        builtins/mx_del_our_node.c \
        builtins/mx_del_variable_env.c \
        builtins/mx_echo.c \
        builtins/mx_last_flag.c \
        builtins/mx_env.c \
        builtins/mx_env_to_ush.c \
        builtins/mx_export.c \
        builtins/mx_fg.c \
        builtins/mx_find_our_node.c \
        builtins/mx_checker_flag.c \
        builtins/mx_clear_path.c \
        builtins/mx_shell_info.c \
        builtins/mx_get_1st_node.c \
        builtins/mx_find_name.c \
        builtins/mx_find_next_tok.c \
        builtins/mx_find_env_path.c \
        builtins/mx_get_tok.c \
        builtins/mx_twight_1.c \
        builtins/mx_new_param.c \
        builtins/mx_jobs.c \
        builtins/mx_many_tabs.c \
        builtins/mx_lone_tab.c \
        builtins/mx_filling_env.c \
        builtins/mx_pwd.c \
        builtins/mx_read_comand.c \
        builtins/mx_return_var.c \
        builtins/mx_find_cur_list.c \
        builtins/mx_unset.c \
        builtins/mx_unset_saved.c \
        builtins/mx_which.c \
		signals/mx_ctrl_r.c \
		exec/mx_exec_dmor.c \
		exec/mx_exec_env_pr.c \
		exec/mx_exec_less.c \
		exec/mx_exec_more.c \
		exec/mx_exec_token.c \
		exec/mx_exec.c \
		exec/mx_exec_proces.c \
		exec/mx_exec_tree.c \
		exec/mx_exec_pipe.c \
		signals/mx_read_keyboard.c \
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
		printing/mx_printerr_env.c \
		printing/mx_print_esc.c \
		printing/mx_print_susp.c \
		printing/mx_print_tab_comands.c \
		printing/mx_printstr_env.c \
		sortings/mx_pop_front_free_data.c \
        sortings/mx_pop_list.c \
        sortings/mx_push_back_res.c \
		utils/main.c \
		utils/bit_function.c \
        utils/main.c \
        utils/mx_xo.c \
        utils/mx_arr_str_to_str.c \
        utils/mx_ascii.c \
        utils/mx_str_check.c \
        utils/mx_chdir_l.c \
        utils/mx_chdir_p.c \
        utils/mx_create_tree.c \
        utils/mx_create_commands.c \
        utils/mx_create_tnode.c \
        utils/mx_create_token.c \
        utils/mx_delete_last.c \
        utils/mx_replace.c \
        utils/mx_dupl_arr_str.c \
        utils/mx_exit.c \
        utils/mx_history.c \
        utils/mx_home.c \
        utils/mx_input.c \
        utils/mx_insert_tree.c \
        utils/mx_is_str_begin.c \
        utils/mx_lexical.c \
        utils/mx_is_ascii.c \
        utils/mx_term_param.c \
        utils/mx_reg.c \
        utils/mx_launch_ush.c \
        utils/mx_bquote_str.c \
        utils/mx_arrstr_to_arrstr.c \
        utils/mx_str_diff.c \
        utils/mx_str_concatenation.c \
        utils/mx_str_merge.c \
        utils/mx_sub_str.c \
        utils/mx_syntax_check.c \
        utils/mx_ush_token.c \
        utils/mx_ush_close.c \
        utils/mx_ush_init.c \
        utils/mx_tree_to_variable.c \
        utils/mx_wait_process.c \
        utils/mx_write_to.c \
        utils/mx_get_char.c \
        utils/mx_terminal_stdout.c \
        utils/mx_add_to_str_arr.c \
        utils/mx_loop.c)



OBJ =	mx_add_new_path.o \
        mx_add_process.o \
        mx_fill_build.o \
        mx_call_env.o \
        mx_cd.o \
        mx_find_env.o \
        mx_close_all_pr.o \
        mx_paste_nonascii.o \
        mx_del_last_var.o \
        mx_del_pid_process.o \
        mx_del_top_process.o \
        mx_del_our_node.o \
        mx_del_variable_env.o \
        mx_echo.o \
        mx_last_flag.o \
        mx_env.o \
        mx_env_to_ush.o \
        mx_export.o \
        mx_fg.o \
        mx_find_our_node.o \
        mx_checker_flag.o \
        mx_clear_path.o \
        mx_shell_info.o \
        mx_get_1st_node.o \
        mx_find_name.o \
        mx_find_next_tok.o \
        mx_find_env_path.o \
        mx_get_tok.o \
        mx_twight_1.o \
        mx_new_param.o \
        mx_jobs.o \
        mx_many_tabs.o \
        mx_lone_tab.o \
        mx_filling_env.o \
        mx_pwd.o \
        mx_read_comand.o \
        mx_return_var.o \
        mx_find_cur_list.o \
        mx_unset.o \
        mx_unset_saved.o \
        mx_which.o \
  		mx_ctrl_r.o \
  		mx_exec_dmor.o \
  		mx_exec_env_pr.o \
  		mx_exec_less.o \
  		mx_exec_more.o \
  		mx_exec_token.o \
  		mx_exec.o \
  		mx_exec_proces.o \
  		mx_exec_tree.o \
  		mx_exec_pipe.o \
  		mx_read_keyboard.o \
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
  		mx_printerr_env.o \
  		mx_print_esc.o \
  		mx_print_susp.o \
  		mx_print_tab_comands.o \
  		mx_printstr_env.o \
  		main.o \
  		bit_function.o \
        mx_xo.o \
        mx_arr_str_to_str.o \
        mx_ascii.o \
        mx_str_check.o \
        mx_chdir_l.o \
        mx_chdir_p.o \
        mx_create_tree.o \
        mx_create_commands.o \
        mx_create_tnode.o \
        mx_create_token.o \
        mx_delete_last.o \
        mx_replace.o \
        mx_dupl_arr_str.o \
        mx_exit.o \
        mx_history.o \
        mx_home.o \
        mx_input.o \
        mx_insert_tree.o \
        mx_is_str_begin.o \
        mx_lexical.o \
        mx_is_ascii.o \
        mx_term_param.o \
        mx_push_back_res.o \
        mx_reg.o \
        mx_launch_ush.o \
        mx_bquote_str.o \
        mx_arrstr_to_arrstr.o \
        mx_str_diff.o \
        mx_str_concatenation.o \
        mx_str_merge.o \
        mx_sub_str.o \
        mx_syntax_check.o \
        mx_ush_token.o \
        mx_ush_close.o \
        mx_ush_init.o \
        mx_tree_to_variable.o \
        mx_wait_process.o \
        mx_write_to.o \
        mx_get_char.o \
        mx_terminal_stdout.o \
        mx_add_to_str_arr.o \
        mx_pop_front_free_data.o \
        mx_pop_list.o \
        mx_loop.o

CC = clang

CFLAGS = -std=c11 -Wall -Wextra -Werror -Wpedantic

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
	@printf "$(APP_NAME) \033[31;1minstalled\033[0m\n"

uninstall : clean
	@make uninstall -C $(LIBMXF)
	@rm -rf $(APP_NAME) $(OBJ)
	@printf "$(APP_NAME) \033[31;1muninstalled\033[0m\n"

clean :
	@make clean -C $(LIBMXF)
	@rm -rf $(OBJ_DIR)
	@printf "$(OBJD)\t   \033[31;1mcleaned\033[0m\n"

reinstall : uninstall install