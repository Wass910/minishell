DEFAULT = \033[0;39m
GRAY = \033[0;90m
RED = \033[0;91m
GREEN = \033[0;92m
YELLOW = \033[0;93m
BLUE = \033[0;94m
MAGENTA = \033[0;95m
CYAN = \033[0;96m
WHITE = \033[0;97m
TESTCOL = \033[1;35m

UNAME = $(shell uname -s)

CFLAGS =-g3 -fsanitize=address -Wall -Wextra -Werror
RM = rm -f
CC1 = clang -lreadline
CC2 = clang
SRC_DIR = src
OBJ_DIR = obj
BIN = minishell
NAME = minishell
INC = inc/minishell.h
ECHO = echo
ECHON = echo -n
ECHOE = printf

SRC = builtin.c check_builtin.c exec_cmd2.c exec_cmd.c flstadd_back.c flstadd_front.c flstclear.c flstdelone.c\
flstiter.c flstlast.c flstmap.c flstnew.c flstsize.c ft_atoi.c ft_split.c ft_strcat.c ft_strchr.c ft_strdup.c\
ft_strjoin.c ft_strlen.c ft_strncmp.c get_next_line.c get_next_line_utils.c get_path.c lst_ope.c minishell.c\
pipex.c sort_env.c utils2.c utils.c strcat.c ft_itoa.c parse_quotes.c quotes_utils.c\
parse_glitch.c free_stab.c open_file.c redirection.c uniq_comm.c lst_cmd.c input_red.c\
parsing_uniq.c build_echo.c build_pwd.c build_unset.c unset_utils.c is_smtg.c glitch_bin.c\
glitch_bin2.c parse_bin.c uniq_bin.c utils_bin.c setup_bin.c pipex_bin.c fill_cbin.c fill_cbin2.c\
fill_cbin3.c delete_bin.c delete_bin2.c setup.c parsing_uniq_norm.c minishell_norm.c pipex_norm.c\
main.c exec_pipe_norm.c exec_pipe.c delete_pair_norme.c free_list.c another_bin.c another_bin2.c\
delete_bin3.c

OBJ = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))

all: $(NAME)

$(NAME): create_dirs $(OBJ)
	@$(CC1) $(CFLAGS) -I $(INC) $(OBJ) -o $@
	@$(ECHON) "                                            \r"
	@$(ECHO) "\rCompilation succed$(GREEN)"
	@$(ECHO) "$(WHITE)$(BIN) is up to date!$(WHITE)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@$(ECHON) "                                            \r"
	@$(ECHON) "Compiling $(GRAY)$<$(GREEN)\r"
	@$(CC2) $(CFLAGS) -I $(INC) -c $< -o $@

create_dirs:
	@mkdir -p $(OBJ_DIR)

clean:
	@$(ECHON) "$(GREEN)Cleaning up object files in $(OBJ_DIR), and $(OBJ_LFT_DIR)...\r"
	@$(ECHON) "                                                                     \r"
	@$(ECHO) "$(GRAY)\rCleaning done"
	@$(RM) -r $(OBJ_DIR)

fclean: clean
	@$(RM) -r $(BIN)
	@$(ECHO) "$(GRAY)Removed $(BIN)$(GREEN)"

norminette:
	@$(ECHO) "$(GRAY)Checking norm for $(BIN)...$(GREEN)"
	@norminette -R CheckForbiddenSourceHeader $(SRC_DIR) inc/

re: fclean all

git:
	git add .
	git commit
	git push

-include $(OBJ_DIR)/*.d

.PHONY: all clean fclean norminette create_dirs re