# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ljerinec <ljerinec@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/05 15:24:20 by ljerinec          #+#    #+#              #
#    Updated: 2023/08/30 01:40:34 by ljerinec         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Wall -Werror -Wextra -g3 -fsanitize=address

SOURCES =	sources/main.c \
			sources/prompt/signal.c \
			sources/prompt/prompt.c \
			sources/parsing/parsing.c \
			sources/parsing/check_arg.c \
			sources/parsing/parsing_atribute.c \
			sources/parsing/ft_split_fou.c \
			sources/parsing/ft_split_fou_utils.c \
			sources/parsing/parsing_utils.c \
			sources/parsing/env_var_expansion.c \
			sources/parsing/ft_split_keep_char.c \
			sources/parsing/quoting.c \
			sources/ast/setup_ast.c \
			sources/freeing/free_chainlink.c \

OBJ_DIR = object
OBJECTS = $(patsubst %.c, %.o, $(SOURCES))

MINISHELL = minishell

LIBFT_DIR = includes/libft/libft.a
FT_PRINTF_DIR = includes/ft_printf/ft_printf.a
INCLUDES_DIR = includes/
READLINE =	$(shell brew --prefix readline)
INC_RL = -I $(READLINE)/include
LINK_RL = -L $(READLINE)/lib -lreadline

####################COMPILATION STYLING####################

TOTAL_FILES = $(words $(SOURCES))
CURRENT_FILE = 0
BAR_WIDTH = 30

PRINT_NAME		:= Minishell
PRINT_PREFIX	:=	\033[1m\033[38;5;240m[\033[0m\033[38;5;250m$(PRINT_NAME)\033[1m\033[38;5;240m] \033[38;5;105m~\033[0m

all: $(MINISHELL)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@ -I $(INCLUDES_DIR) $(INC_RL)
	@$(eval CURRENT_FILE=$(shell echo $$(($(CURRENT_FILE)+1))))
	@$(eval PROGRESS=$(shell echo $$(($(CURRENT_FILE) * $(BAR_WIDTH) / $(TOTAL_FILES)))))
	@$(eval REMAINING=$(shell echo $$(($(BAR_WIDTH) - $(PROGRESS)))))

	@printf "$(PRINT_PREFIX) \033[1;33m[$(CURRENT_FILE)/$(TOTAL_FILES)] ["
	@printf "%${PROGRESS}s" | tr ' ' '■'
	@printf "%${REMAINING}s" | tr ' ' ' '
	@printf "]\r\033[0m"

$(MINISHELL): $(OBJECTS)
	@make -C includes/libft
	@$(CC) $(CFLAGS) -o $(MINISHELL) $(OBJECTS) $(LIBFT_DIR) $(FT_PRINTF_DIR) $(LINK_RL)
	@printf "$(PRINT_PREFIX) \033[1;32m[$(CURRENT_FILE)/$(TOTAL_FILES)] ["
	@printf "%${PROGRESS}s" | tr ' ' '■'
	@printf "%${REMAINING}s" | tr ' ' ' '
	@printf "][OK]\n\033[0m"

clean:
	@make -C includes/libft clean
	@rm -f $(OBJECTS)

fclean: clean
	@make -C includes/libft fclean
	@rm -f $(MINISHELL)

re: fclean all

.PHONY: all clean fclean re
