/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaguen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 05:22:10 by  souaguen         #+#    #+#             */
/*   Updated: 2023/11/16 21:42:21 by souaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_min(size_t a, size_t b)
{
	if (a < b)
		return (a);
	return (b);
}

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	d_len;
	size_t	i;

	d_len = ft_strlen(dest);
	i = d_len - 1;
	if (size == 0)
		return (ft_strlen(src));
	while ((++i) < (size - 1) && *(src + (i - d_len)) != '\0')
		*(dest + i) = *(src + (i - d_len));
	if (size > d_len)
		*(dest + i) = '\0';
	return (ft_strlen(src) + ft_min(size, d_len));
}
