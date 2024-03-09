/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaguen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 21:33:03 by souaguen          #+#    #+#             */
/*   Updated: 2023/11/17 14:30:34 by souaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	buf[2];
	size_t			i;

	i = 0;
	while (i < n)
	{
		buf[0] = *(unsigned char *)(s1 + i);
		buf[1] = *(unsigned char *)(s2 + i);
		if (buf[0] != buf[1])
			return (buf[0] - buf[1]);
		i++;
	}
	return (0);
}
