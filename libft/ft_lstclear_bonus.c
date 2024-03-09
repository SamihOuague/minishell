/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaguen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 00:33:44 by  souaguen         #+#    #+#             */
/*   Updated: 2023/11/15 23:34:57 by souaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*cursor;
	t_list	*tmp;

	if (del == NULL)
		return ;
	cursor = *lst;
	while (cursor != NULL)
	{
		tmp = (*cursor).next;
		ft_lstdelone(cursor, del);
		cursor = tmp;
	}
	*lst = NULL;
}
