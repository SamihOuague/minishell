/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaguen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 01:10:14 by  souaguen         #+#    #+#             */
/*   Updated: 2023/11/13 02:52:40 by souaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	nbr_len(int n)
{
	unsigned int	len;
	unsigned int	i;

	i = n;
	len = 0;
	if (n < 0)
	{
		i = -1 * n;
		len++;
	}
	else if (n == 0)
		return (1);
	while (i > 0)
	{
		i = i / 10;
		len++;
	}
	return (len);
}

static unsigned int	ft_abs(int n)
{
	if (n < 0)
		return (n * -1);
	return (n);
}

char	*ft_itoa(int n)
{
	unsigned int	c;
	unsigned int	i;
	char			*str;
	int				len;

	len = nbr_len(n);
	str = malloc((sizeof(char) * len) + 1);
	if (str == NULL)
		return (NULL);
	i = 0;
	c = ft_abs(n);
	if (n < 0)
		*(str + (i++)) = '-';
	if (n >= 0)
		len--;
	while (c > 0)
	{
		*(str + (len - i++)) = (c % 10) + '0';
		c = c / 10;
	}
	if (n == 0)
		*(str + (i++)) = '0';
	*(str + i) = '\0';
	return (str);
}
