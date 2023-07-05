# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ljerinec <ljerinec@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/05 15:24:20 by ljerinec          #+#    #+#              #
#    Updated: 2023/07/05 16:17:23 by ljerinec         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = Minishell

SRCS =	sources/main.c \

OBJS = $(SRCS:%.c=%.o)

CFLAGS = -Wall -Werror -Wextra
CC = gcc

PRINT_NAME		:= Minishell
PRINT_PREFIX	:=	\033[1m\033[38;5;240m[\033[0m\033[38;5;250m$(PRINT_NAME)\033[1m\033[38;5;240m] \033[38;5;105m~\033[0m

INCLUDES_DIR = includes/
LIBFT_DIR = includes/libft/libft.a
PRINTF_DIR = includes/ft_printf/libftprintf.a

all: $(NAME)


$(NAME): $(OBJS)
	@make -C ../libft
	@echo "$(PRINT_PREFIX)\033[0;38;5;226m Compiling \033[0m\n"
	@$(CC) $(CFLAGS) -o $(NAME) -I$(INCLUDES_DIR) $(LIBFT_DIR) $(PRINTF_DIR) $(OBJS)
	@echo "$(PRINT_PREFIX)\033[0;38;5;226m Done \033[0m\n"

clean:
	@make -C ../libft clean
	@echo "$(PRINT_PREFIX)\033[0;38;5;226m Cleaning \033[0m\n"
	@rm -f $(OBJS)
	@echo "$(PRINT_PREFIX)\033[0;38;5;226m Done \033[0m\n"

%.o:  %.c
	@$(CC) -c $(CFLAGS) -I $(INCLUDES_DIR)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re