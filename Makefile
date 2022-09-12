GREEN = "\033[1;32m"
RED = "\033[1;31m"
YELLOW = "\033[1;33m"
BLUE = "\033[1;34m"
WHITE = "\033[1;37m"
RESET = "\033[0m"

NAME = minishell

PROJECT = MINISHELL

SRCS = minishell.c \
		$(addprefix srcs/signals/, signals.c exit_code.c) \
		$(addprefix srcs/lexer/, lexer.c lexer_elmt_utils.c find_type.c char_handling.c) \
		$(addprefix srcs/parser/, parser.c quote_handling.c find_next_quote.c var_handling.c pipe_handling.c q_tokens_handling.c) \
		$(addprefix srcs/redirections/, redirections_errors.c redirections_handling.c redirections_utils.c heredoc_redirections.c input_redirections.c output_redirections.c recreate_and_exec.c) \
		$(addprefix srcs/builtins/, free_list.c pwd.c unset.c unset_utils.c env.c exit.c cd.c echo.c export.c export_utils.c list_env.c list_env_utils.c set_build.c print.c cd_utils.c echo_utils.c export_init.c export_add.c) \
		$(addprefix srcs/execution/, execution.c finders.c) \

OBJS = $(SRCS:.c=.o)

CFLAGS = -Wall -Wextra -Werror

HEADER = -I./includes -I./includes/libft/ -I./includes/gnl -I./includes/readline/include

all: $(NAME)

rl:
	@rm -rf req.sh
	@rm -rf t
	@printf "\033[1;33m"
	@echo "if [[ ! -d "includes/readline" ]]" > req.sh
	@echo "then" >> req.sh
	@echo "\ttouch readline-8.1.tar.gz" >> req.sh
	@echo "\techo "Creating readline library..."" >> req.sh
	@echo "\tcurl -ks https://ftp.gnu.org/gnu/readline/readline-8.1.tar.gz > readline-8.1.tar.gz" >> req.sh
	@echo "\t(tar -xf readline-8.1.tar.gz) >> t"  >> req.sh
	@echo "\tmv readline-8.1 readline" >> req.sh
	@echo "\trm -rf readline-8.1.tar.gz" >> req.sh
	@echo "\tmv readline includes" >> req.sh
	@echo "\tcd includes/readline/" >> req.sh
	@echo "\t(./configure --prefix=$$(pwd)/includes/readline) >> t" >> req.sh
	@echo "\tmake && make install && make clean" >> req.sh
	@echo "\trm -rf t" >> req.sh
	@echo "\tcd ../../" >> req.sh
	@echo "\tclear" >> req.sh
	@echo "\techo "📁 SUCCESS: readline folder has been created!"" >> req.sh
	@echo "fi" >> req.sh
	@sh req.sh
	@rm -rf t
	@rm -rf req.sh
	@stty -echoctl

.c.o: $(SRCS)
	@make rl
	@printf $(GREEN)"\r\033[KCreating object files 👉 "$(YELLOW)"<$<> "$(RESET)
	@gcc $(CFLAGS) $(HEADER) -c $< -o $(<:.c=.o)

$(NAME): $(OBJS)
	@make bonus -C includes/libft/
	@gcc $(CFLAGS) $(HEADER) -o $(NAME) -L includes/libft -lft $(SRCS) -lreadline -L./includes/readline/lib -lncurses
	@printf $(GREEN)"\r\033[K✅ SUCCESS: "$(WHITE)$(NAME)$(GREEN)" has been created\n"$(RESET)

$(NAME)_sanitize: $(SRCS)
	@gcc $(CFLAGS) -fsanitize=address -g $(HEADER) -o $(NAME)_sanitize -L includes/libft -lft $(SRCS) -lreadline -L./includes/readline/lib -lncurses

clean:
	@rm -rf $(OBJS) 
	@rm -rf includes/readline
	@make clean -C includes/libft
	@printf $(RED)"\r\033[K➜ ["$(PROJECT)"] "$(WHITE)"clean"$(RED)" has been done\n"$(RESET)
	@printf $(RED)"\r\033[K➜ [READLINE] library folder has been "$(WHITE)"removed"$(RED)"\n"$(RESET)

fclean:
	@rm -rf $(OBJS)
	@rm -rf includes/readline
	@rm -rf $(NAME)
	@rm -rf includes/libft/libft.a
	@make fclean -C includes/libft
	@printf $(RED)"\r\033[K➜ [READLINE] library folder has been "$(WHITE)"removed"$(RED)"\n"$(RESET)
	@printf $(RED)"\r\033[K➜ ["$(PROJECT)"] "$(WHITE)"clean"$(RED)" has been done\n"$(RESET)
	@printf $(RED)"\r\033[K➜ ["$(PROJECT)"] "$(WHITE)"fclean"$(RED)" has been done\n"$(RESET)

re: fclean all

fre:
	@rm -rf $(OBJS) 
	@make clean -C includes/libft
	@printf $(RED)"\r\033[K➜ ["$(PROJECT)"] "$(WHITE)"clean"$(RED)" has been done\n"$(RESET)
	@rm -rf $(OBJS)
	@rm -rf $(NAME)
	@rm -rf includes/libft/libft.a
	@make fclean -C includes/libft
	@printf $(RED)"\r\033[K➜ ["$(PROJECT)"] "$(WHITE)"clean"$(RED)" has been done\n"$(RESET)
	@printf $(RED)"\r\033[K➜ ["$(PROJECT)"] "$(WHITE)"fclean"$(RED)" has been done\n"$(RESET)
	@make all

.PHONY: all clean fclean re rl
