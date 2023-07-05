# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ljerinec <ljerinec@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/25 23:06:56 by ljerinec          #+#    #+#              #
#    Updated: 2023/07/05 15:17:00 by ljerinec         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

SRC = 	ft_printf.c \
		ft_putchar.c \
		ft_putnbr.c \
		ft_putnbr_hexa.c \
		ft_putstr.c \

OBJECTS = $(SRC:.c=.o)

CC = gcc
CFLAGS = -Wall -Werror -Wextra

PRINT_NAME		:= ft_printf
PRINT_PREFIX	:=	\033[1m\033[38;5;240m[\033[0m\033[38;5;250m$(PRINT_NAME)\033[1m\033[38;5;240m] \033[38;5;105m~\033[0m

all: $(NAME) 

$(NAME): $(OBJECTS)
	@echo "$(PRINT_PREFIX)\033[0;38;5;226m Compiling \033[0m\n"
	@AR -rc $@ $?
	@echo "$(PRINT_PREFIX)\033[0;38;5;226m Done \033[0m\n"

%.o:  %.c
	@$(CC) -c $(CFLAGS) $?

clean:
	@echo "$(PRINT_PREFIX)\033[0;38;5;226m Cleaning \033[0m\n"
	@rm -f $(OBJECTS) $(BONUS)
	@echo "$(PRINT_PREFIX)\033[0;38;5;226m Done \033[0m\n"

fclean: clean
	rm -f $(NAME)

re: fclean all
