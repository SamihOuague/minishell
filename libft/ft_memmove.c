/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaguen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 03:13:26 by  souaguen         #+#    #+#             */
/*   Updated: 2023/11/17 14:49:20 by souaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char	tmp;
	int		i;

	if (src == NULL && dest == NULL)
		return (NULL);
	if (dest >= src)
	{
		i = n - 1;
		while (i >= 0)
		{
			tmp = *(char *)(src + i);
			*(char *)(dest + i) = tmp;
			i--;
		}
	}
	else
		return (ft_memcpy(dest, src, n));
	return (dest);
}
