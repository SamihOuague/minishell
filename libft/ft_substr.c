/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaguen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 02:27:49 by  souaguen         #+#    #+#             */
/*   Updated: 2023/11/13 02:15:16 by souaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_min(size_t a, size_t b)
{
	if (a > b)
		return (b);
	return (a);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	i;
	size_t	s_len;

	i = 0;
	s_len = ft_strlen(s);
	if (start > s_len || len == 0)
	{
		str = malloc(1);
		if (str == NULL)
			return (NULL);
		*(str) = '\0';
		return (str);
	}
	s_len = get_min(ft_strlen((s + start)), len);
	str = malloc(s_len * sizeof(char) + 1);
	if (str == NULL)
		return (NULL);
	while (i < len && *(s + (start + i)) != '\0')
	{
		*(str + i) = *(s + (start + i));
		i++;
	}
	*(str + i) = '\0';
	return (str);
}
