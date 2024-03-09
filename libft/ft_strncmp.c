/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaguen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 06:07:11 by  souaguen         #+#    #+#             */
/*   Updated: 2024/03/09 10:20:16 by souaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (s1 == NULL || s2 == NULL)
		return (-1);
	if (n <= 0)
		return (0);
	while (*(s1 + i) == *(s2 + i) && *(s1 + i) != '\0' && i < (n - 1))
		i++;
	return ((int)((unsigned char)*(s1 + i) - (unsigned char)*(s2 + i)));
}
