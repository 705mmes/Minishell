# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ljerinec <ljerinec@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/31 11:51:02 by ljerinec          #+#    #+#              #
#    Updated: 2022/10/31 11:51:23 by ljerinec         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRCS =	ft_strlen.c \
		ft_atoi_long_long.c \
		ft_atoi.c \
		ft_bzero.c \
		ft_isascii.c \
		ft_isprint.c \
		ft_strlcpy.c \
		ft_strdup.c \
		ft_memcmp.c \
		ft_memchr.c	\
		ft_calloc.c \
		ft_putstr_fd.c \
		ft_substr.c	\
		ft_split.c \
		ft_lstnew.c \
		ft_lstadd_front.c \
		ft_lstsize.c \
		ft_lstlast.c \
		ft_strncmp.c \
		ft_lstadd_back.c \
		ft_lstdelfirst.c \
		ft_lstdellast.c \
		ft_itoa.c \
		ft_strjoin.c \
		get_next_line.c \
		get_next_line_utils.c \

OBJS = $(SRCS:%.c=%.o)

CFLAGS = -Wall -Werror -Wextra
CC = gcc

PRINT_NAME		:= libft
PRINT_PREFIX	:=	\033[1m\033[38;5;240m[\033[0m\033[38;5;250m$(PRINT_NAME)\033[1m\033[38;5;240m] \033[38;5;105m~\033[0m

all: $(NAME)

$(NAME): $(OBJS)
	@make -C ../ft_printf
	@echo "$(PRINT_PREFIX)\033[0;38;5;226m Compiling \033[0m\n"
	@ar -rcs $(NAME) $(OBJS) $?
	@echo "$(PRINT_PREFIX)\033[0;38;5;226m Done \033[0m\n"

clean:
	@make -C ../ft_printf clean
	@echo "$(PRINT_PREFIX)\033[0;38;5;226m Cleaning \033[0m\n"
	@rm -f $(OBJS)
	@echo "$(PRINT_PREFIX)\033[0;38;5;226m Done \033[0m\n"

%.o:  %.c
	@$(CC) -c $(CFLAGS) $?

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
