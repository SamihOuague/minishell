/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaguen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 04:44:03 by  souaguen         #+#    #+#             */
/*   Updated: 2023/11/16 21:24:44 by souaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	next_sep(char *s, char c)
{
	int	i;

	i = 1;
	while (*(s + i) != '\0')
	{
		if (*(s + i) == c)
			return (i);
		i++;
	}
	return (i);
}

static char	*skip_first_chars(char *s, char c)
{
	int	i;

	i = 0;
	if (s == NULL)
		return (NULL);
	while (*(s + i) == c && *(s + i) != '\0')
		i++;
	return (s + i);
}

static int	count_words(char *s, char c)
{
	int	i;
	int	count;
	int	b;

	i = 0;
	b = 0;
	count = 0;
	if (s == NULL || *(s) == '\0')
		return (0);
	while (*(s + i + 1) != '\0')
	{
		if (*(s + i) == c && *(s + i + 1) != c && b)
			count++;
		if (!b && *(s + i) != c)
			b = 1;
		i++;
	}
	return (count + 1);
}

static void	free_tab(char **tab, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

char	**ft_split(char const *s, char c)
{
	char	**tab;
	int		count;
	int		i;
	int		b;

	s = skip_first_chars((char *)s, c);
	count = count_words((char *)s, c);
	tab = malloc(sizeof(char *) * (count + 1));
	if (tab == NULL)
		return (NULL);
	i = 0;
	while (*(s) != '\0')
	{
		b = next_sep((char *)s, c);
		tab[i] = ft_substr((char *)s, 0, b);
		if (tab[(i++)] == NULL)
		{
			free_tab(tab, i);
			return (NULL);
		}
		s = skip_first_chars((char *)(s + b), c);
	}
	tab[i] = NULL;
	return (tab);
}
