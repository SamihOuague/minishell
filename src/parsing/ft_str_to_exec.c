/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_to_exec.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouajjou <iouajjou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 22:26:46 by souaguen          #+#    #+#             */
/*   Updated: 2024/07/29 17:27:48 by souaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_skip_cursor(t_list **lst, t_token **token)
{
	t_list	*cursor;
	t_token	*t;
	char	*str;
	char	*tmp;

	cursor = *lst;
	t = NULL;
	while (cursor != NULL)
	{
		if ((*cursor).next != NULL)
			t = (*(*cursor).next).content;
		if ((*cursor).next != NULL
			&& !(!(*t).quoted && ft_strchr(" >|<", *(*t).str)))
		{
			tmp = (**token).str;
			str = (*(t_token *)(*(*cursor).next).content).str;
			(**token).str = ft_strjoin((**token).str, str);
			free(tmp);
			cursor = (*cursor).next;
		}
		else
			break ;
	}
	*lst = cursor;
}

char	**ft_convert_list(t_list *lst)
{
	t_token	*token;
	t_list	*cursor;
	char	**argv;
	int		siz;

	siz = ft_lstsize(lst);
	argv = malloc(sizeof(char *) * (siz + 1));
	if (argv == NULL)
		return (NULL);
	argv[siz] = NULL;
	siz = 0;
	cursor = lst;
	while (cursor != NULL)
	{
		token = (*cursor).content;
		argv[siz] = (*token).str;
		cursor = (*cursor).next;
		siz++;
	}
	free_lst(lst);
	return (argv);
}

void	ft_skip_file(t_list **lst)
{
	t_list	*cursor;
	t_token	*token;

	cursor = *lst;
	while (cursor != NULL)
	{
		token = (*cursor).content;
		if (ft_strncmp((*token).str, " ", 2))
			break ;
		cursor = (*cursor).next;
	}
	if (cursor == NULL)
	{
		*lst = NULL;
		return ;
	}
	cursor = (*cursor).next;
	while (cursor != NULL)
	{
		token = (*cursor).content;
		if (!(*token).quoted)
			break ;
		cursor = (*cursor).next;
	}
	*lst = cursor;
}

void	ft_skip_empty(t_list **lst)
{
	t_list	*cursor;
	t_token	*token;

	if (lst == NULL || *lst == NULL)
		return ;
	cursor = *lst;
	token = (*cursor).content;
	while (*(*token).str == '\0' && (*token).quoted == 0)
	{
		cursor = (*cursor).next;
		if (cursor != NULL)
			token = (*cursor).content;
		else
			break ;
	}
	*lst = cursor;
}

char	**lst_to_argv(t_list *lst)
{
	t_token	*token;
	t_list	*cursor;
	t_list	*new;

	new = NULL;
	cursor = lst;
	ft_skip_empty(&cursor);
	while (cursor != NULL)
	{
		token = (*cursor).content;
		if ((!ft_strncmp((*token).str, "<", 2)
				|| !ft_strncmp((*token).str, ">", 2)) && !(*token).quoted)
			ft_skip_file(&cursor);
		else if (!((*token).quoted == 0 && !ft_strncmp((*token).str, " ", 2)))
		{
			ft_skip_cursor(&cursor, &token);
			ft_lstadd_back(&new, ft_lstnew(token));
		}
		if (cursor == NULL)
			break ;
		cursor = (*cursor).next;
	}
	return (ft_convert_list(new));
}
