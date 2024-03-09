/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaguen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 03:01:03 by  souaguen         #+#    #+#             */
/*   Updated: 2023/11/16 21:44:21 by souaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	int		len_1;
	int		len_2;
	int		i;

	len_1 = ft_strlen(s1);
	len_2 = ft_strlen(s2);
	str = malloc(sizeof(char) * (len_1 + len_2) + 1);
	if (str == NULL)
		return (NULL);
	i = 0;
	while (i < (len_1 + len_2))
	{
		if (i < len_1)
			*(str + i) = *(s1 + i);
		else
			*(str + i) = *(s2 + (i - len_1));
		i++;
	}
	*(str + i) = '\0';
	return (str);
}
