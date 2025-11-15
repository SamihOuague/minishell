/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaguen <souaguen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 15:35:43 by souaguen          #+#    #+#             */
/*   Updated: 2024/06/17 17:22:14 by souaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_get_tmp(char *str, t_token **token)
{
	char	*tmp;

	tmp = str;
	(**token).quoted = 0;
	if (*(str) == '\'' && ft_strchr((str + 1), '\''))
	{
		(**token).quoted = 1;
		tmp = ft_strtrim(str, "\'");
	}
	else if (*(str) == '\"' && ft_strchr((str + 1), '\"'))
	{
		(**token).quoted = 2;
		tmp = ft_strtrim(str, "\"");
	}
	return (tmp);
}

void	*update_line(void *content)
{
	t_token	*token;
	char	*tmp;
	char	*str;

	if (content == NULL)
		return (NULL);
	str = (char *)content;
	token = malloc(sizeof(t_token));
	if (token == NULL)
		return (NULL);
	tmp = ft_get_tmp(str, &token);
	if (tmp == NULL)
	{
		free(token);
		return (NULL);
	}
	(*token).str = tmp;
	if ((*token).quoted == 0)
		(*token).str = ft_strdup(tmp);
	return ((void *)token);
}

void	free_quoted(void *ptr)
{
	t_token	*token;

	token = ptr;
	if (token != NULL)
	{
		free((*token).str);
		(*token).str = NULL;
		free(ptr);
		ptr = NULL;
	}
}

static void	*ft_free_err(t_list *l, char *b, char *t)
{
	free(b);
	free(t);
	ft_lstclear(&l, free);
	return (NULL);
}

t_list	*parsing_init(char *cmd, t_sys *sys)
{
	t_list	*lst;
	t_list	*swp;
	char	*token;
	char	*backup;
	char	*str;

	(void)sys;
	str = ft_strdup(cmd);
	backup = str;
	lst = NULL;
	if (str == NULL)
		return (NULL);
	token = ft_strtok(&str, " ><|");
	while (token)
	{
		token = ft_exitcode_handler(token, sys);
		swp = ft_lstnew(token);
		if (swp == NULL)
			return (ft_free_err(lst, backup, token));
		ft_lstadd_back(&lst, swp);
		token = ft_strtok(&str, " ><|");
	}
	swp = ft_lstmap(lst, &update_line, &free_quoted);
	ft_free_err(lst, backup, NULL);
	return (swp);
}
