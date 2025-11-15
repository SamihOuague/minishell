/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cleaning_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouajjou <iouajjou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 10:23:13 by souaguen          #+#    #+#             */
/*   Updated: 2024/08/29 15:39:39 by iouajjou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tree(t_tree **root)
{
	if (root == NULL || *root == NULL)
		return ;
	free_tree(&(**root).left);
	free_tree(&(**root).right);
	free((**root).content);
	(**root).content = NULL;
	free(*root);
	*root = NULL;
}

void	free_all(t_sys *sys)
{
	free_tree(&(*sys).root);
	ft_lstclear(&(*sys).lst, &free_quoted);
	ft_lstclear(&(*sys).backup, &free_quoted);
	ft_lstclear(&(*sys).pipeline, &ft_free_pipeline);
	free(sys->input);
	(*sys).root = NULL;
	(*sys).lst = NULL;
	(*sys).backup = NULL;
	(*sys).pipeline = NULL;
	(*sys).input = NULL;
}

void	close_fds(void *content)
{
	int	*tab;

	tab = (int *) content;
	close(tab[0]);
}

int	end_shell(t_sys *sys)
{
	clear_history();
	free_all(sys);
	free_envp((*sys).envp_backup);
	ft_lstclear(&(*sys).local_env, free);
	free(*sys->envp);
	*sys->envp = NULL;
	(*sys).local_env = NULL;
	sys->envp_backup = NULL;
	ft_lstclear(&(sys->fds), close_fds);
	return (1);
}

void	free_lst(t_list *lst)
{
	t_list	*cursor;
	t_list	*tmp;

	cursor = lst;
	while (cursor != NULL)
	{
		tmp = (*cursor).next;
		free(cursor);
		cursor = tmp;
	}
}
