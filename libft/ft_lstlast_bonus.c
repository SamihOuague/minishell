/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaguen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 00:25:21 by  souaguen         #+#    #+#             */
/*   Updated: 2023/11/13 00:54:03 by souaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*cursor;

	if (lst == NULL)
		return (NULL);
	cursor = lst;
	while ((*cursor).next != NULL)
		cursor = (*cursor).next;
	return (cursor);
}
