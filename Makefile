# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: souaguen <souaguen@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/08 21:52:24 by  souaguen         #+#    #+#              #
#    Updated: 2024/03/13 01:59:10 by souaguen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC=cc
CFLAGS=-g -I./libft -I./#-Wall -Wextra -Werror
SRC=main.c \
    src/ft_str_parsing.c
NAME=minishell
OBJ=$(SRC:.c=.o)

$(NAME): $(OBJ)
	make -C libft all bonus
	$(CC) -g $(OBJ) -o $(NAME) -L./libft -l:libft.a -lreadline

all: $(NAME)

clean:
	rm -f $(OBJ) $(BONUS)
	make -C libft clean

fclean: clean
	rm -f $(NAME)
	make -C libft fclean

re: fclean all

.PHONY: all clean fclean re
