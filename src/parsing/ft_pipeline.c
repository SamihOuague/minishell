/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipeline.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouajjou <iouajjou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 05:07:16 by souaguen          #+#    #+#             */
/*   Updated: 2024/07/25 23:21:30 by iouajjou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*get_next_pipe(t_list **lst)
{
	t_token	*token;
	t_list	*cursor;
	t_list	*new;

	new = NULL;
	cursor = *lst;
	while (cursor != NULL)
	{
		token = (*cursor).content;
		if ((*token).quoted == 0 && !ft_strncmp((*token).str, "|", 2))
		{
			*lst = (*cursor).next;
			return (new);
		}
		ft_lstadd_back(&new, ft_lstnew(token));
		cursor = (*cursor).next;
	}
	*lst = NULL;
	return (new);
}

int	ft_tab_size(char **argv)
{
	int	i;

	i = 0;
	while (argv[i] != NULL)
		i++;
	return (i);
}

void	ft_pipeln_init(t_pipeline **pipln, t_list *new)
{
	(**pipln).eof = NULL;
	(**pipln).a_mode = 0;
	(**pipln).file = get_files(new);
	(**pipln).argv = lst_to_argv(new);
	(**pipln).argc = ft_tab_size((**pipln).argv);
	(**pipln).fd_in = 0;
	(**pipln).fd_out = 1;
	(**pipln).exit_code = 0;
	ft_lstclear(&new, &ft_null);
}

t_list	*ft_pipeline_init(t_list *parsed)
{
	t_pipeline	*pipln;
	t_list		*pipeline;
	t_list		*new;

	new = NULL;
	pipeline = NULL;
	while (parsed != NULL)
	{
		new = get_next_pipe(&parsed);
		pipln = malloc(sizeof(t_pipeline));
		if (pipln == NULL || new == NULL)
		{
			ft_lstclear(&new, &ft_null);
			free(pipln);
			ft_lstclear(&pipeline, free_quoted);
			return (NULL);
		}
		ft_pipeln_init(&pipln, new);
		ft_lstadd_back(&pipeline, ft_lstnew(pipln));
	}
	return (pipeline);
}
