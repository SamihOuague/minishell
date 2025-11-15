# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: iouajjou <iouajjou@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/07 02:16:23 by souaguen          #+#    #+#              #
#    Updated: 2024/07/25 16:46:12 by iouajjou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC=cc
CFLAGS=-g -Wall -Werror -Wextra -I./get_next_line -I./libft -I./includes
NAME=minishell
EXECSRC=src/exec/builtins.c \
	 src/exec/child.c \
	 src/exec/env.c \
	 src/exec/exec.c \
	 src/exec/parent.c \
	 src/exec/pipe.c \
	 src/exec/system.c \
	 src/exec/utils.c \
	 src/exec/utils_plus.c \
	 src/exec/signal.c \
	 src/exec/unset.c \
	 src/exec/exec_utils.c \
	 main.c
PARSINGSRC=src/parsing/ft_env_parsing.c \
	    src/parsing/ft_file_utils.c \
	    src/parsing/ft_parsing.c \
	    src/parsing/ft_pipeline.c \
	    src/parsing/ft_strtok.c \
	    src/parsing/ft_str_to_exec.c \
	    src/parsing/ft_parsing_utils.c \
	    src/parsing/ft_file_tools.c \
	    src/parsing/ft_syntax_check.c \
	    src/parsing/ft_cleaning_utils.c \
	    src/parsing/ft_exitcode.c
WILDCARDSRC=src/wildcard/ft_wildcard.c \
	    src/wildcard/ft_wildcard_utils.c \
	    src/wildcard/ft_wildcard_tools.c \
	    src/wildcard/ft_dir_loop.c
LIBTREEDIR=src/libtree
LIBTREESRC=$(LIBTREEDIR)/ft_tree.c \
	   $(LIBTREEDIR)/ft_tree_utils.c \
	   $(LIBTREEDIR)/ft_exec_tree.c
GNLSRC=src/get_next_line/get_next_line.c \
       src/get_next_line/get_next_line_utils.c
EXECOBJ=$(EXECSRC:.c=.o)
PARSINGOBJ=$(PARSINGSRC:.c=.o)
LIBTREEOBJ=$(LIBTREESRC:.c=.o)
WILDCARDOBJ=$(WILDCARDSRC:.c=.o)
GNLOBJ=$(GNLSRC:.c=.o)

$(NAME): $(EXECOBJ) $(PARSINGOBJ) $(LIBTREEOBJ) $(GNLOBJ) $(WILDCARDOBJ)
	make -C libft all bonus
	$(CC) $(EXECOBJ) $(PARSINGOBJ) $(LIBTREEOBJ) $(GNLOBJ) $(WILDCARDOBJ) -o $(NAME) -L./libft -l:libft.a -lreadline

all: $(NAME)

clean:
	make -C libft clean
	rm -f $(EXECOBJ) $(PARSINGOBJ) $(LIBTREEOBJ) $(GNLOBJ) $(WILDCARDOBJ)

fclean: clean
	make -C libft fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
