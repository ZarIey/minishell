GREEN = "\033[1;32m"
RED = "\033[1;31m"
YELLOW = "\033[1;33m"
BLUE = "\033[1;34m"
WHITE = "\033[1;37m"
RESET = "\033[0m"

NAME = minishell

PROJECT = MINISHELL

SRCS =	minishell.c \
		list_env.c  \
		$(addprefix srcs/prompt/, prompt.c) \
		$(addprefix srcs/signals/, signals.c) \
		$(addprefix srcs/lexer/, lexer.c) \
		$(addprefix srcs/parser/, parser.c) \
		$(addprefix srcs/commands/, commands.c) \
		$(addprefix srcs/builtins/, pwd.c unset.c env.c exit.c cd.c echo.c export.c) \
		$(addprefix includes/gnl/, get_next_line.c get_next_line_utils.c) \

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

.c.o: $(SRCS)
	@make rl
	@printf $(GREEN)"\r\033[KCreating object files 👉 "$(YELLOW)"<$<> "$(RESET)
	@gcc $(CFLAGS) $(HEADER) -c $< -o $(<:.c=.o)

$(NAME): $(OBJS)
	@make bonus -C includes/libft/
	@gcc $(CFLAGS) $(HEADER) -o $(NAME) -L includes/libft -lft $(SRCS) -L includes/readline/lib -lreadline
	@printf $(GREEN)"\r\033[K✅ SUCCESS: "$(WHITE)$(NAME)$(GREEN)" has been created\n"$(RESET)

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
