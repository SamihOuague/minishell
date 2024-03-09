/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaguen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 00:23:58 by  souaguen         #+#    #+#             */
/*   Updated: 2023/11/13 00:48:09 by souaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	t_list	*cursor;
	int		size;

	cursor = lst;
	size = 0;
	while (cursor != NULL)
	{
		cursor = (*cursor).next;
		size++;
	}
	return (size);
}
