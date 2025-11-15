/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wildcard_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaguen <souaguen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 12:48:19 by  souaguen         #+#    #+#             */
/*   Updated: 2024/06/13 14:14:51 by souaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_start_end_init(t_list **lst, char *str, int *start_by, int *end_by)
{
	char	*tmp;
	int		len;

	*end_by = *(char *)(*ft_lstlast(*lst)).content != '\0';
	*start_by = *(char *)(**lst).content != '\0';
	len = ft_strlen((**lst).content);
	if (start_by && ft_strncmp(str, (**lst).content, len))
		return (0);
	len = ft_strlen((*ft_lstlast(*lst)).content);
	tmp = (*ft_lstlast(*lst)).content;
	if (end_by
		&& ((int)ft_strlen(str) < len
			|| ft_strncmp(str + (ft_strlen(str) - len), tmp, len)))
		return (0);
	else
		*lst = (**lst).next;
	if (*lst == NULL)
		return (1);
	return (-1);
}

int	ft_wildcard_match(t_list *lst, char *str)
{
	t_list	*cursor;
	int		e;	
	int		l;
	int		i;

	cursor = lst;
	i = ft_start_end_init(&cursor, str, &l, &e);
	if (i != -1)
		return (i);
	i = -1;
	l = ft_strlen((*cursor).content);
	while (*(str + (++i)) != '\0' && cursor != NULL)
	{
		if (ft_strncmp(str + i, (*cursor).content, l) == 0)
		{
			if (!(e && (*cursor).next == NULL && l != (int)ft_strlen(str + i)))
			{
				i += (l - 1);
				cursor = (*cursor).next;
			}
			if (cursor != NULL)
				l = ft_strlen((*cursor).content);
		}
	}
	return (ft_skip_null(cursor));
}

void	ft_init_update_str(char **ptr, char **word, t_list **w, t_token *t)
{
	char	*backup;

	*word = ft_strchr((*t).str, '*');
	*(*word) = '\0';
	backup = *ptr;
	if (*ptr == NULL)
		*ptr = "";
	*ptr = ft_strjoin(*ptr, (*t).str);
	*(*word) = '*';
	free(backup);
	ft_lstadd_back(w, ft_lstnew(*ptr));
	(*t).str = *word + 1;
	*word = ft_strchr((*t).str, '*');
	*ptr = NULL;
}

void	ft_update_str(char **ptr, t_list **w, t_list *c, t_token *t)
{
	char	*word;
	char	*last;

	word = NULL;
	last = (*t).str;
	ft_init_update_str(ptr, &word, w, t);
	while (word != NULL)
	{
		*(word) = '\0';
		ft_lstadd_back(w, ft_lstnew(ft_strdup((*t).str)));
		*(word) = '*';
		(*t).str = word + 1;
		word = ft_strchr((*t).str, '*');
	}
	if (*(*t).str != '\0')
		*ptr = ft_strdup((*t).str);
	else if (*(*t).str == '\0' && (*c).next == NULL)
		ft_lstadd_back(w, ft_lstnew(ft_strdup((*t).str)));
	(*t).str = last;
}

t_list	*ft_extract_wildcard(t_list *lst)
{
	t_list	*cursor;
	t_list	*wordlist;
	t_token	*token;
	char	*tmp;

	tmp = NULL;
	cursor = lst;
	wordlist = NULL;
	while (cursor != NULL)
	{
		token = (*cursor).content;
		if ((*token).quoted == 0
			&& ft_strchr((*token).str, '*'))
			ft_update_str(&tmp, &wordlist, cursor, token);
		else
			tmp = ft_new_tmp(tmp, token);
		cursor = (*cursor).next;
	}
	if (tmp != NULL && *tmp != '\0')
		ft_lstadd_back(&wordlist, ft_lstnew(tmp));
	else
		free(tmp);
	return (wordlist);
}
