/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaguen <souaguen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 10:59:19 by souaguen          #+#    #+#             */
/*   Updated: 2024/06/12 11:53:22 by souaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_check_delim(char **ptr, const char *delim, int i)
{
	char	*str;
	char	*tmp;

	str = *ptr;
	if (ft_strchr(delim, *(str + i))
		|| (*(str + i) == '\'' || *(str + i) == '\"'))
	{
		if (i == 0)
			i = 1;
		tmp = ft_substr(str, 0, i);
		*ptr = (*ptr + i);
		if (**ptr == '\0')
			*ptr = NULL;
		return (tmp);
	}
	return (NULL);
}

char	*ft_extract_quote(char **ptr)
{
	char	*str;
	char	*tmp;
	int		n;

	str = *ptr;
	if ((*(str) == '\'' || *(str) == '\"')
		&& ft_strchr((str + 1), *(str)))
	{
		n = ft_strchr((str + 1), *(str)) - str + 1;
		tmp = ft_substr(str, 0, n);
		*ptr = (*ptr + n);
		if (**ptr == '\0')
			*ptr = NULL;
		return (tmp);
	}
	return (NULL);
}

char	*ft_strtok(char **ptr, const char *delim)
{
	char	*str;
	char	*tmp;
	int		i;

	i = 0;
	if (ptr == NULL || *ptr == NULL)
		return (NULL);
	tmp = ft_extract_quote(ptr);
	if (tmp != NULL)
		return (tmp);
	str = *ptr;
	while (*(str + i) != '\0')
	{
		tmp = ft_check_delim(ptr, delim, i);
		if (tmp != NULL)
			return (tmp);
		i++;
	}
	*ptr = NULL;
	return (ft_strdup(str));
}
