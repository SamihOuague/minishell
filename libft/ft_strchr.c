/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaguen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 05:51:54 by  souaguen         #+#    #+#             */
/*   Updated: 2023/11/17 15:17:21 by souaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (*(s + i) != '\0')
	{
		if ((int) *(s + i) == (char unsigned) c)
			return ((char *)(s + i));
		i++;
	}
	if (*(s + i) == (unsigned char) c)
		return ((char *)(s + i));
	return (NULL);
}
