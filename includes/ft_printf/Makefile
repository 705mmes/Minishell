# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ljerinec <ljerinec@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/25 23:06:56 by ljerinec          #+#    #+#              #
#    Updated: 2023/09/14 20:00:32 by ljerinec         ###   ########.fr        #
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
	@rm -f *.o

fclean: clean
	@rm -f $(FT_PRINTF)
	@rm -f *.a

re: fclean all

.PHONY: all clean fclean re