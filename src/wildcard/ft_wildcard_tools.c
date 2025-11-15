/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wildcard_tools.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaguen <souaguen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 10:03:12 by  souaguen         #+#    #+#             */
/*   Updated: 2024/06/13 10:09:30 by souaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_skip_null(t_list *lst)
{
	t_list	*cursor;

	cursor = lst;
	while (cursor != NULL && *(char *)(*cursor).content == '\0')
		cursor = (*cursor).next;
	return (cursor == NULL);
}

char	*ft_new_tmp(char *backup, t_token *token)
{
	char	*tmp;

	if (backup == NULL)
		backup = ft_strdup("");
	tmp = ft_strjoin(backup, (*token).str);
	free(backup);
	return (tmp);
}

void	ft_wildcard_null_check(t_list **w, t_list **s, t_list **l, t_list *c)
{
	if (*w != NULL)
	{
		if (*s != *l)
			ft_wildcard_util(s, w, c);
		else
			ft_lstclear(w, ft_null);
	}
}

void	*ft_copy_content(void *content)
{
	t_token	*token;
	t_token	*tmp;

	tmp = content;
	token = malloc(sizeof(t_token));
	if (token == NULL)
		return (NULL);
	(*token).str = ft_strdup((*tmp).str);
	(*token).quoted = (*tmp).quoted;
	return (token);
}

t_token	*ft_create_token(char *str, int quoted)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (token == NULL)
		return (NULL);
	(*token).quoted = quoted;
	(*token).str = ft_strdup(str);
	return (token);
}
