/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaguen <souaguen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 01:24:00 by  souaguen         #+#    #+#             */
/*   Updated: 2024/03/16 02:29:12 by souaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include <stdio.h>

t_list	*get_pipeline(t_list *lst)
{
	t_quote_str	*q_str;
	t_list		*pipeline;
	t_list		*cursor;
	char			*tmp;

	tmp = "";
	pipeline = NULL;
	cursor = lst;
	while (cursor != NULL)
	{
		q_str = (*cursor).content;
		if ((*q_str).quoted == 0 && ft_strchr((*q_str).str, '|'))
		{
			*(ft_strchr((*q_str).str, '|')) = '\0';

			break ;
		}
		else
		{
			ft_lstadd_back(&pipeline, ft_lstnew());
		}
		printf("%d:%s\n", (*q_str).quoted, (*q_str).str);
		free((*(t_quote_str *)(*cursor).content).str);
		cursor = (*cursor).next;
	}
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_list	*lst;
	t_list	*cursor;

	lst = NULL;
	if (argc != 2)
		return (1);
	lst = remove_quotes(argv[1]);
	get_pipeline(lst);

/*
	cursor = lst;
	while (cursor != NULL)
	{
		printf("%s\n", (*(t_quote_str *)(*cursor).content).str);
		free((*(t_quote_str *)(*cursor).content).str);
		cursor = (*cursor).next;
	}
*/
	ft_lstclear(&lst, &free);
	return (0);
}
