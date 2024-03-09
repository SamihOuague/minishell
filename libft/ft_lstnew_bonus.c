/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaguen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 00:21:17 by  souaguen         #+#    #+#             */
/*   Updated: 2023/11/15 23:44:48 by souaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*l;

	l = NULL;
	l = malloc(sizeof(t_list));
	if (l == NULL)
		return (NULL);
	(*l).content = content;
	(*l).next = NULL;
	return (l);
}
