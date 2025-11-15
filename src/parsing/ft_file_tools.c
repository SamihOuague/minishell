/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_file_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaguen <souaguen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 11:24:42 by  souaguen         #+#    #+#             */
/*   Updated: 2024/06/25 20:27:23 by souaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_join_next(t_list *cursor)
{
	t_token	*token;
	char	*str;
	char	*tmp;

	token = (*cursor).content;
	str = ft_strdup((*token).str);
	if (str == NULL)
		return (NULL);
	cursor = (*cursor).next;
	while (cursor != NULL)
	{
		token = (*cursor).content;
		if ((*token).quoted == 0
			&& (*(*token).str == ' '
				|| ft_strchr("<|>", *(*token).str)))
			break ;
		tmp = str;
		str = ft_strjoin(str, (*token).str);
		free(tmp);
		cursor = (*cursor).next;
	}
	return (str);
}

char	*ft_skip_whitespace(t_list **lst)
{
	t_token	*token;
	t_list	*cursor;
	t_list	*tmp;

	cursor = *lst;
	while (cursor != NULL)
	{
		token = (*cursor).content;
		if (ft_strncmp((*token).str, " ", 2))
			break ;
		tmp = cursor;
		cursor = (*cursor).next;
		free(tmp);
	}
	*lst = cursor;
	if (cursor == NULL)
		return (NULL);
	return (ft_join_next(cursor));
}
