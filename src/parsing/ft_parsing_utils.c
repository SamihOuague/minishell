/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouajjou <iouajjou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 17:35:12 by souaguen          #+#    #+#             */
/*   Updated: 2024/07/29 17:20:10 by souaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "get_next_line.h"

void	read_file(int fd, int fd_out)
{
	char	buf;

	while (read(fd, &buf, 1) > 0)
		ft_putchar_fd(buf, fd_out);
}

char	*get_name_fd(void)
{
	unsigned char	buf[11];
	int				fd;
	int				i;

	fd = open("/dev/random", O_RDONLY);
	if (fd == -1)
		return (NULL);
	read(fd, buf, 10);
	buf[10] = 0;
	close(fd);
	i = -1;
	while (buf[++i])
		buf[i] = (buf[i] % 26) + 97;
	buf[0] = '.';
	return (ft_strdup((const char *)buf));
}

int	ft_io_syntax(t_sys *sys, int *i, int *b)
{
	char	quoted;

	quoted = '\0';
	while (*((*sys).input + *i) != '\0')
	{
		if (*((*sys).input + *i) == quoted && ++(*i))
			quoted = '\0';
		else if (ft_strchr("><", *((*sys).input + *i)) && quoted == '\0')
		{
			*b = 1;
			*i += 1 + (*((*sys).input + *i) == *((*sys).input + *i + 1));
		}
		if ((ft_isalnum(*((*sys).input + *i))
				|| ft_strchr("\'\"", *((*sys).input + *i)))
			&& quoted == '\0')
			*b = 0;
		if (*b == 1 && *((*sys).input + *i) == '|' && quoted == '\0')
			return (0);
		else if (ft_strchr("\'\"", *((*sys).input + *i)) && quoted == '\0')
			quoted = *((*sys).input + *i);
		(*i)++;
	}
	return (1);
}
