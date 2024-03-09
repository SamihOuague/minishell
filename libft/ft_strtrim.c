/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaguen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 04:12:39 by  souaguen         #+#    #+#             */
/*   Updated: 2023/11/16 21:55:33 by souaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_in_set(char const *set, char c)
{
	int	i;

	if (set == NULL)
		return (0);
	i = 0;
	while (*(set + i) != '\0')
	{
		if (*(set + i) == c)
			return (1);
		i++;
	}
	return (0);
}

static int	count_chars(char const *s, char const *set)
{
	char	b;
	int		i;
	int		c;

	i = 0;
	c = 0;
	b = 0;
	while (*(s + i) != '\0')
	{
		if (is_in_set(set, *(s + i)) && !b)
			c++;
		else if (!b)
			b = 1;
		i++;
	}
	if (c == i)
		return (c);
	while ((i--) > 0)
	{
		if (is_in_set(set, *(s + i)))
			c++;
		else
			break ;
	}
	return (c);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	size_t	n;
	size_t	i;
	size_t	j;

	if (s1 == NULL)
		return (NULL);
	n = count_chars(s1, set);
	str = malloc((ft_strlen(s1) - n) * sizeof(char) + 1);
	if (str == NULL)
		return (NULL);
	i = 0;
	while (is_in_set(set, *(s1 + i)))
		i++;
	n = n - i;
	j = 0;
	while (*(s1 + (i + n)) != '\0')
	{
		*(str + j) = *(s1 + i);
		i++;
		j++;
	}
	*(str + j) = '\0';
	return (str);
}
