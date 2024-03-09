/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaguen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 22:01:33 by souaguen          #+#    #+#             */
/*   Updated: 2023/11/17 15:45:27 by souaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	l_len;

	i = 0;
	l_len = ft_strlen(little);
	if ((len <= 0 && l_len > 0)
		|| (l_len > len && little != NULL && big != NULL))
		return (NULL);
	else if (l_len == 0)
		return ((char *)(big));
	while (*(big + i) != '\0' && i <= (len - l_len))
	{
		if (ft_strncmp((big + i), (char *)(little), l_len) == 0)
			return ((char *)(big + i));
		i++;
	}
	return (NULL);
}
