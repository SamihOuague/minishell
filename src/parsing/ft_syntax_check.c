/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_syntax_check.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaguen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 10:36:29 by souaguen          #+#    #+#             */
/*   Updated: 2024/06/15 11:12:27 by souaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_token_checker(t_token *token)
{
	if ((*token).quoted != 0
		|| (*(*token).str != ' ' && ft_isprint(*(*token).str)))
		return (1);
	else if ((*token).quoted == 0
		&& ft_strchr("&<|>", *(*token).str))
		return (0);
	return (-1);
}

int	ft_next_token_check(t_list *lst)
{
	t_token	*token;
	t_token	*tmp;
	t_list	*cursor;

	cursor = lst;
	if (cursor == NULL || (*cursor).next == NULL)
		return (0);
	token = (*cursor).content;
	tmp = (*(*cursor).next).content;
	if ((*tmp).quoted == 0 && *(*token).str == *(*tmp).str)
		cursor = (*cursor).next;
	cursor = (*cursor).next;
	while (cursor != NULL)
	{
		token = (*cursor).content;
		if (ft_token_checker(token) != -1)
			return (ft_token_checker(token));
		cursor = (*cursor).next;
	}
	return (1);
}

int	ft_syntax_check(t_list *lst)
{
	t_token	*token;
	t_list	*cursor;

	cursor = lst;
	token = (*cursor).content;
	while (cursor != NULL)
	{
		token = (*cursor).content;
		if ((*token).quoted == 0
			&& *(*token).str
			&& ft_strchr("<|>", *(*token).str)
			&& !ft_next_token_check(cursor))
			return (0);
		cursor = (*cursor).next;
	}
	return (1);
}

int	ft_tree_checker(t_tree *root, t_list *lst, char c)
{
	if (*(char *)(*root).content == '\0'
		|| (ft_strncmp((*root).content, "&&", 3)
			&& ft_strncmp((*root).content, "||", 3)
			&& (!ft_syntax_check(lst)
				|| ft_strchr("&|", c)
				|| ft_strchr("&|", *(char *)(*root).content))))
		return (1);
	return (0);
}

int	ft_check_tree(t_tree *root, t_sys *sys)
{
	t_list	*lst;
	char	tmp;
	int		len;

	if (root == NULL || (*root).content == NULL)
		return (1);
	lst = parsing_init((*root).content, sys);
	len = ft_strlen((*root).content);
	tmp = *(char *)(*root).content;
	if (len > 0)
		tmp = *(char *)((*root).content + (len - 1));
	if (ft_tree_checker(root, lst, tmp))
	{
		ft_lstclear(&lst, free_quoted);
		return (0);
	}
	ft_lstclear(&lst, free_quoted);
	if (!ft_check_tree((*root).left, sys))
		return (0);
	if (!ft_check_tree((*root).right, sys))
		return (0);
	return (1);
}
