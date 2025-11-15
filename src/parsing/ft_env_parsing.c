/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_parsing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouajjou <iouajjou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 18:03:31 by souaguen          #+#    #+#             */
/*   Updated: 2024/08/29 17:00:26 by souaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_something(char *content, int quoted)
{
	char	*env;
	char	*tmp;

	if (*(content) != '$'
		|| (*(content) == '$' && *(content + 1) == '\0'))
		return (ft_strdup(content));
	env = getenv(content + 1);
	if (env == NULL)
		env = "";
	env = ft_strdup(env);
	if (quoted == 0)
	{
		tmp = env;
		env = ft_strtrim(env, " ");
		free(tmp);
	}
	return (env);
}

char	*ft_lstto_str(t_list **lst, int quoted)
{
	t_list	*cursor;
	char	*str;
	char	*tmp;
	char	*tmpp;

	cursor = *lst;
	str = ft_strdup("");
	while (cursor != NULL)
	{
		tmp = str;
		tmpp = ft_something((*cursor).content, quoted);
		str = ft_strjoin(str, tmpp);
		free(tmp);
		free(tmpp);
		cursor = (*cursor).next;
	}
	ft_lstclear(lst, free);
	return (str);
}

char	*ft_replace_env(t_token *token)
{
	t_list	*lst;
	char	*str;
	char	backup;
	int		i;
	int		start;

	i = 0;
	start = 0;
	lst = NULL;
	str = (*token).str;
	while (*(char *)(str + i) != '\0')
	{
		if (!ft_strchr("_", *(str + i)) && !ft_isalnum(*(str + i)))
		{
			backup = *(char *)(str + i);
			*(char *)(str + i) = '\0';
			ft_lstadd_back(&lst, ft_lstnew(ft_strdup(str + start)));
			*(char *)(str + i) = backup;
			start = i;
		}
		i++;
	}
	ft_lstadd_back(&lst, ft_lstnew(ft_strdup(str + start)));
	return (ft_lstto_str(&lst, (*token).quoted));
}

void	*ft_env(void *content)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (token == NULL)
		return (NULL);
	if ((*(t_token *)content).quoted == 1)
		(*token).str = ft_strdup((*(t_token *)content).str);
	else
		(*token).str = ft_replace_env(content);
	(*token).quoted = (*(t_token *)content).quoted;
	return (token);
}
