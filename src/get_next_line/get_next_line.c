/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaguen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 01:39:13 by  souaguen         #+#    #+#             */
/*   Updated: 2024/01/06 05:27:23 by souaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_get_str_size(t_gnlist *l, char *str)
{
	t_gnlist	*cursor;
	int			j;
	int			i;

	i = 0;
	cursor = l;
	if (str != NULL)
	{
		while (*(str + i) != '\0')
			i++;
		return (i);
	}
	while (cursor != NULL)
	{
		j = 0;
		while ((*cursor).content[j] != '\0')
			j++;
		i += j;
		cursor = (*cursor).next;
	}
	return (i);
}

char	*ft_get_str(t_gnlist **l)
{
	t_gnlist	*cursor;
	char		*str;
	int			j;
	int			i;
	int			size;

	size = ft_get_str_size(*l, NULL);
	if (size == 0)
		return (NULL);
	str = malloc(sizeof(char) * size + 1);
	if (str == NULL)
		return (NULL);
	cursor = *l;
	i = 0;
	while (cursor != NULL)
	{
		j = -1;
		while ((*cursor).content[++j] != '\0')
			*(str + (j + i)) = (*cursor).content[j];
		i += j;
		cursor = (*cursor).next;
	}
	*(str + i) = '\0';
	ft_lstclear_gnl(l);
	return (str);
}

int	ft_set_list(t_gnlist **lst, char *buf)
{
	char	*str;
	int		len;
	int		n_line;

	len = ft_get_str_size(NULL, buf);
	n_line = find_newline(buf, BUFFER_SIZE);
	str = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (str == NULL)
		return (0);
	if (n_line >= 0)
	{
		ft_memcpy(str, buf, n_line + 1);
		*(str + n_line + 1) = '\0';
		ft_memcpy(buf, (buf + n_line + 1), BUFFER_SIZE - n_line);
		if (n_line == (len - 1))
			ft_memset(buf, 0, BUFFER_SIZE);
	}
	else
	{
		ft_memcpy(str, buf, BUFFER_SIZE + 1);
		if (n_line == -1)
			ft_memset(buf, 0, BUFFER_SIZE);
	}
	return (ft_lstadd_back_gnl(lst, str, buf));
}

char	*get_next_line(int fd)
{
	static char	buf[BUFFER_SIZE + 1] = {0};
	t_gnlist	*l;
	int			n_read;

	l = NULL;
	if (ft_get_str_size(NULL, buf) > 0 && ft_set_list(&l, buf) != 0)
		return (ft_get_str(&l));
	n_read = read(fd, buf, BUFFER_SIZE);
	while (n_read > 0)
	{
		ft_set_list(&l, buf);
		if (find_newline(buf, BUFFER_SIZE) >= -1)
			break ;
		ft_memset(buf, 0, BUFFER_SIZE);
		n_read = read(fd, buf, BUFFER_SIZE);
	}
	if (n_read < 0)
		return (ft_lstclear_gnl(&l));
	return (ft_get_str(&l));
}
