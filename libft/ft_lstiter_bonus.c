/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaguen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 00:34:38 by  souaguen         #+#    #+#             */
/*   Updated: 2023/11/15 23:38:11 by souaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	t_list	*cursor;

	if (f == NULL)
		return ;
	cursor = lst;
	while (cursor != NULL)
	{
		(*f)((*cursor).content);
		cursor = (*cursor).next;
	}
}
