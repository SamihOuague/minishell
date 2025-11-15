/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wildcard.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaguen <souaguen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 00:40:47 by  souaguen         #+#    #+#             */
/*   Updated: 2024/06/13 11:17:09 by souaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*ft_list_match(t_list *wildcard)
{
	t_list			*f_list;
	t_list			*wordlist;

	f_list = NULL;
	wordlist = ft_extract_wildcard(wildcard);
	ft_dir_loop(&f_list, wordlist);
	if (f_list == NULL)
		f_list = ft_lstmap(wildcard, ft_copy_content, free);
	ft_lstclear(&wordlist, free);
	return (f_list);
}

int	ft_has_wildcard(t_list *wildcard)
{
	t_token	*token;
	t_list	*cursor;

	cursor = wildcard;
	while (cursor != NULL)
	{
		token = (*cursor).content;
		if ((*token).quoted == 0 && ft_strchr((*token).str, '*'))
			return (1);
		cursor = (*cursor).next;
	}
	return (0);
}

void	ft_free_old(t_list **lst)
{
	t_token	*token;
	t_list	*cursor;
	t_list	*tmp;

	if (lst == NULL || *lst == NULL)
		return ;
	cursor = (**lst).next;
	while (cursor != NULL)
	{
		token = (*cursor).content;
		if ((*token).quoted == 0 && !ft_strncmp((*token).str, " ", 2))
			break ;
		free((*token).str);
		free(token);
		tmp = (*cursor).next;
		free(cursor);
		cursor = tmp;
	}
}

void	ft_wildcard_util(t_list **start, t_list **wildcard, t_list *lst)
{
	t_list	*f_list;

	if (ft_has_wildcard(*wildcard))
	{
		f_list = ft_list_match(*wildcard);
		(*ft_lstlast(f_list)).next = lst;
		ft_free_old(start);
		if (*start != NULL)
			(**start).next = f_list;
	}
	ft_lstclear(wildcard, ft_null);
	*start = NULL;
	*wildcard = NULL;
}

void	ft_wildcard(t_list **lst)
{
	t_token	*token;
	t_list	*wildcard;
	t_list	*cursor;
	t_list	*last;
	t_list	*start;

	start = NULL;
	wildcard = NULL;
	last = NULL;
	cursor = *lst;
	while (cursor != NULL)
	{
		token = (*cursor).content;
		if (!((*token).quoted == 0 && ft_strchr(" <|>", *(*token).str)))
		{
			if (start == NULL)
				start = last;
			ft_lstadd_back(&wildcard, ft_lstnew(token));
		}
		else if (wildcard != NULL)
			ft_wildcard_util(&start, &wildcard, cursor);
		last = cursor;
		cursor = (*cursor).next;
	}
	ft_wildcard_null_check(&wildcard, &start, lst, cursor);
}
