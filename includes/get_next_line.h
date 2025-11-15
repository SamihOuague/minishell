/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaguen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 01:38:05 by  souaguen         #+#    #+#             */
/*   Updated: 2024/01/04 16:48:50 by souaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include "libft.h"

typedef struct s_gnlist
{
	char			*content;
	struct s_gnlist	*next;
}	t_gnlist;

void	*ft_lstclear_gnl(t_gnlist **lst);
char	*get_next_line(int fd);
char	*ft_get_str(t_gnlist **l);
int		find_newline(char *buf, size_t size);
int		ft_get_str_size(t_gnlist *l, char *str);
int		ft_lstadd_back_gnl(t_gnlist **list, char *new, char *buf);
#endif
