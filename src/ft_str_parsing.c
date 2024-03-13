/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_parsing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaguen <souaguen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 01:29:55 by  souaguen         #+#    #+#             */
/*   Updated: 2024/03/13 05:57:42 by souaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	push_back_str(t_list **lst, char **ptr, int *index, char c)
{
	char	*sw_tmp;
	char	*tmp;
	int		i;

	i = *index;
	tmp = *ptr;
	sw_tmp = NULL;
	if (i > 0)
	{
		*(tmp + i) = '\0';
		ft_lstadd_back(lst, ft_lstnew(ft_strdup(tmp)));
		*(tmp + i) = c;
	}
	tmp = (tmp + i + 1);
	sw_tmp = ft_strchr(tmp, c);
	*(sw_tmp) = '\0';
	ft_lstadd_back(lst, ft_lstnew(ft_strdup(tmp)));
	tmp = sw_tmp + 1;
	*index = -1;
	*ptr = tmp;
}

int	ft_close_quote(char *str)
{
	return ((*(str) == '\'' && ft_strchr((str + 1), '\''))
		|| (*(tmp) == '\"' && ft_strchr((str + 1), '\"')));
}

t_list	*remove_quotes(char *str)
{
	t_list	*new_str;
	char	*tmp;
	char	c_tmp;
	int		i;

	i = -1;
	new_str = NULL;
	tmp = str;
	while (*(tmp + (++i)) != '\0')
	{
		if (ft_close_quote((tmp + i)))
			push_back_str(&new_str, &tmp, &i, *(tmp + i));
		else if (*(tmp + i) == ' ')
		{
			c_tmp = *(tmp + i + 1);
			*(tmp + i + 1) = '\0';
			ft_lstadd_back(&new_str, ft_lstnew(ft_strdup(tmp)));
			*(tmp + i + 1) = c_tmp;
			tmp = (tmp + i + 1);
			i = -1;
		}
	}
	if (*(tmp) != '\0')
		ft_lstadd_back(&new_str, ft_lstnew(ft_strdup(tmp)));
	return (new_str);
}
