/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaguen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 06:02:12 by  souaguen         #+#    #+#             */
/*   Updated: 2023/11/17 15:17:54 by souaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*tmp;
	int		i;

	i = 0;
	tmp = NULL;
	while (*(s + i) != '\0')
	{
		if (*(s + i) == (unsigned char) c)
			tmp = (char *)(s + i);
		i++;
	}
	if (*(s + i) == (unsigned char) c)
		return ((char *)(s + i));
	return (tmp);
}
