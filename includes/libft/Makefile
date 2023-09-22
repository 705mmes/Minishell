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

CC = gcc
CFLAGS = -Wall -Werror -Wextra

SOURCES =	ft_strlen.c \
			ft_atoi_long_long.c \
			ft_atoi.c \
			ft_bzero.c \
			ft_isascii.c \
			ft_isprint.c \
			ft_strlcpy.c \
			ft_tolower.c \
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
			ft_lstadd_here.c \
			ft_lstdelfirst.c \
			ft_lstdellast.c \
			ft_lstdel_here.c \
			ft_itoa.c \
			ft_strjoin.c \
			ft_strchr.c \
			../get_next_line/get_next_line.c \
			../get_next_line/get_next_line_utils.c \

OBJECTS = $(patsubst %.c, %.o, $(SOURCES))

LIBFT = libft.a

####################COMPILATION STYLING####################

TOTAL_FILES = $(words $(SOURCES))
CURRENT_FILE = 0
BAR_WIDTH = 30

PRINT_NAME		:= libft
PRINT_PREFIX	:=	\033[1m\033[38;5;240m[\033[0m\033[38;5;250m$(PRINT_NAME)\033[1m\033[38;5;240m] \033[38;5;105m~\033[0m

all: $(LIBFT)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@
	@$(eval CURRENT_FILE=$(shell echo $$(($(CURRENT_FILE)+1))))
	@$(eval PROGRESS=$(shell echo $$(($(CURRENT_FILE) * $(BAR_WIDTH) / $(TOTAL_FILES)))))
	@$(eval REMAINING=$(shell echo $$(($(BAR_WIDTH) - $(PROGRESS)))))

	@printf "$(PRINT_PREFIX) \033[1;33m[$(CURRENT_FILE)/$(TOTAL_FILES)] ["
	@printf "%${PROGRESS}s" | tr ' ' '■'
	@printf "%${REMAINING}s" | tr ' ' ' '
	@printf "]\r\033[0m"
	
$(LIBFT): $(OBJECTS)
	@make -C ../ft_printf
	@ar -rcs $@ $(OBJECTS)
	@printf "$(PRINT_PREFIX) \033[1;32m[$(CURRENT_FILE)/$(TOTAL_FILES)] ["
	@printf "%${PROGRESS}s" | tr ' ' '■'
	@printf "%${REMAINING}s" | tr ' ' ' '
	@printf "][OK]\r\033[0m"
	@printf "\n"

clean:
	@make -C ../ft_printf clean
	@rm -f $(OBJECTS)
	@rm -f *.o
	@rm -f ../get_next_line/*.o

fclean: clean
	@make -C ../ft_printf fclean
	@rm -f $(LIBFT)
	@rm -f *.a

re: fclean all

.PHONY: all clean fclean re

