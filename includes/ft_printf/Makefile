# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ljerinec <ljerinec@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/25 23:06:56 by ljerinec          #+#    #+#              #
#    Updated: 2023/07/06 00:50:12 by ljerinec         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Wall -Werror -Wextra

SOURCES = 	ft_printf.c \
		ft_putchar.c \
		ft_putnbr.c \
		ft_putnbr_hexa.c \
		ft_putstr.c \

OBJECTS = $(patsubst %.c, %.o, $(SOURCES))

FT_PRINTF = ft_printf.a

all: $(FT_PRINTF)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@
	
$(FT_PRINTF): $(OBJECTS)
	@ar -rcs $@ $(OBJECTS)

clean:
	@rm -f $(OBJECTS)

fclean: clean
	@rm -f $(FT_PRINTF)

re: fclean all

.PHONY: all clean fclean re