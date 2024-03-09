# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: souaguen <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/05 06:10:54 by  souaguen         #+#    #+#              #
#    Updated: 2023/11/20 13:47:28 by souaguen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC=cc
SRCS=ft_atoi.c \
     ft_itoa.c \
     ft_putendl_fd.c \
     ft_strlcat.c \
     ft_substr.c \
     ft_bzero.c \
     ft_putnbr_fd.c \
     ft_strlcpy.c \
     ft_tolower.c \
     ft_calloc.c \
     ft_memchr.c \
     ft_putstr_fd.c \
     ft_strlen.c \
     ft_toupper.c \
     ft_isalnum.c \
     ft_memcmp.c \
     ft_split.c \
     ft_strmapi.c \
     ft_isalpha.c \
     ft_memcpy.c \
     ft_strchr.c \
     ft_strncmp.c \
     ft_isascii.c \
     ft_memmove.c \
     ft_strdup.c \
     ft_strnstr.c \
     ft_isdigit.c \
     ft_memset.c \
     ft_striteri.c \
     ft_strrchr.c \
     ft_isprint.c \
     ft_putchar_fd.c \
     ft_strjoin.c \
     ft_strtrim.c
BONUSRC=ft_lstdelone_bonus.c \
	ft_lstadd_back_bonus.c \
	ft_lstclear_bonus.c \
	ft_lstadd_front_bonus.c \
	ft_lstsize_bonus.c \
	ft_lstnew_bonus.c \
	ft_lstmap_bonus.c \
	ft_lstlast_bonus.c \
	ft_lstiter_bonus.c 
NAME=libft.a
OBJ=$(SRCS:.c=.o)
BONUS=$(BONUSRC:.c=.o)
CFLAGS=-Wall -Werror -Wextra -I./

$(NAME): $(OBJ)
	ar rc $(NAME) $(OBJ)

all: $(NAME)

clean:
	rm -f $(OBJ) $(BONUS)
fclean: clean
	rm -f $(NAME)
re: fclean all

bonus: $(BONUS)
	ar rc $(NAME) $(BONUS)

.PHONY: all clean fclean re bonus
