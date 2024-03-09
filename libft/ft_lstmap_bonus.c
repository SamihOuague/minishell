/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaguen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 00:35:35 by  souaguen         #+#    #+#             */
/*   Updated: 2023/11/20 11:02:11 by souaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*list;
	t_list	*cursor;
	t_list	*tmp;

	list = NULL;
	cursor = lst;
	while (cursor != NULL)
	{
		tmp = ft_lstnew((f)((*cursor).content));
		if (tmp == NULL)
		{
			ft_lstclear(&list, del);
			return (NULL);
		}
		ft_lstadd_back(&list, tmp);
		cursor = (*cursor).next;
	}
	return (list);
}
