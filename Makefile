# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sammeuss <sammeuss@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/05 23:42:48 by ljerinec          #+#    #+#              #
#    Updated: 2023/09/13 17:33:07 by sammeuss         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Wall -Werror -Wextra -g3 

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
			sources/parsing/lexing_cmds.c \
			sources/parsing/quoting.c \
			sources/parsing/file_and_redir.c \
			sources/parsing/heredoc_gestion.c \
			sources/freeing/free_chainlink.c \
			sources/pipex/pipex.c \
			sources/pipex/pipex_main.c \
			sources/builtins/pwd.c \
			sources/builtins/echo.c \
			sources/builtins/cd.c \
			sources/builtins/env.c \
			sources/builtins/unset.c \
			sources/builtins/export.c \
			sources/builtins/builtins_utils.c \

OBJ_DIR = object/
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
