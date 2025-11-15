/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaguen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 22:42:43 by  souaguen         #+#    #+#             */
/*   Updated: 2024/01/06 05:27:48 by souaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*ft_lstclear_gnl(t_gnlist **lst)
{
	t_gnlist	*tmp;
	t_gnlist	*cursor;

	cursor = *lst;
	while (cursor != NULL)
	{
		tmp = (*cursor).next;
		free((*cursor).content);
		free(cursor);
		cursor = tmp;
	}
	return (NULL);
}

int	ft_lstadd_back_gnl(t_gnlist **lst, char *new, char *buf)
{
	t_gnlist	*cursor;
	int			size;

	cursor = *lst;
	size = ft_get_str_size(NULL, buf);
	if (cursor == NULL)
	{
		*lst = malloc(sizeof(t_list));
		(**lst).content = new;
		(**lst).next = NULL;
		return (size);
	}
	while ((*cursor).next != NULL)
		cursor = (*cursor).next;
	(*cursor).next = malloc(sizeof(t_list));
	if ((*cursor).next == NULL)
		return (0);
	(*(*cursor).next).content = new;
	(*(*cursor).next).next = NULL;
	return (size);
}

int	find_newline(char *buf, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		if (buf[i] == '\n')
			return (i);
		else if (buf[i] == '\0')
			return (-1);
		i++;
	}
	return (-2);
}
