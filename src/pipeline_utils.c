/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaguen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 01:51:48 by souaguen          #+#    #+#             */
/*   Updated: 2024/03/19 05:37:33 by souaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

char	*replace_content(char *str, char *l_str)
{
	char	*tmp;
	char	*res;

	tmp = str;
	res = ft_strjoin(str, l_str);
	free(tmp);
	return (res);
}

t_quote_str	*ft_parse_vars(t_quote_str *quoted_str)
{
	t_quote_str	*q_str;
	char		*str;

	q_str = quoted_str;
	str = (*q_str).str;
	if ((*q_str).quoted != 1 && ft_strchr((*q_str).str, '$'))
		(*q_str).str = var_to_str((*q_str).str);
	return (q_str);
}

t_list	*get_pipeline(t_list *lst)
{
	t_quote_str	*q_str;	
	t_quote_str	*q_tmp;
	t_list		*cmd;
	t_list		*pipeline;
	t_list		*cursor;
	char			*tmp;
	char			*tmpp;
	char			*backup;

	cmd = NULL;
	cursor = lst;
	pipeline = NULL;
	tmp = NULL;
	while (cursor != NULL)
	{
		q_str = ft_parse_vars((*cursor).content);
		if ((*q_str).quoted == 0 && ft_strchr((*q_str).str, '|'))
		{
			tmp = (*q_str).str;
			backup = ft_strchr(tmp, '|');
			*backup = '\0';
			q_tmp = malloc(sizeof(t_quote_str));
			(*q_tmp).quoted = 0;
			(*q_tmp).str = ft_strdup(tmp);
			ft_lstadd_back(&cmd, ft_lstnew(q_tmp));
			ft_lstadd_back(&pipeline, ft_lstnew(cmd));
			(*q_str).str = ft_strdup(backup + 1);
		}
		else
		{
			ft_lstadd_back(&cmd, ft_lstnew(q_str));
			cursor = (*cursor).next;
		}
	}
	//ft_lstadd_back(&pipeline, ft_lstnew(cmd));
	return (pipeline);
}
