/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaguen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 01:44:32 by  souaguen         #+#    #+#             */
/*   Updated: 2023/11/20 10:34:26 by souaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*buf;

	buf = NULL;
	if (size == 0)
	{
		buf = malloc(0);
		if (buf == NULL)
			return (NULL);
		return (buf);
	}
	else if ((nmemb * size) / size != nmemb)
		return (NULL);
	buf = malloc(nmemb * size);
	if (buf == NULL)
		return (NULL);
	ft_bzero(buf, size * nmemb);
	return (buf);
}
