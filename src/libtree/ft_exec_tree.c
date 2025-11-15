/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_tree.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouajjou <iouajjou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 10:03:18 by  souaguen         #+#    #+#             */
/*   Updated: 2024/08/29 15:39:28 by iouajjou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ast.h"
#include "minishell.h"

void	ft_free_file(void *content)
{
	t_file	*f;

	f = content;
	if (f != NULL)
	{
		if ((*f).eof != NULL)
			unlink((*f).name);
		free((*f).name);
		free((*f).eof);
		(*f).name = NULL;
		(*f).eof = NULL;
		free(f);
	}
}

void	ft_free_pipeline(void *content)
{
	t_pipeline	*pipeline;

	pipeline = content;
	if (pipeline != NULL)
	{
		free((*pipeline).argv);
		ft_lstclear(&(*pipeline).file, ft_free_file);
		(*pipeline).argv = NULL;
		(*pipeline).file = NULL;
	}
	free(content);
	content = NULL;
}

void	ft_reset_pipeline(t_sys *sys)
{
	ft_lstclear(&(*sys).lst, &free_quoted);
	ft_lstclear(&(*sys).backup, &free_quoted);
	ft_lstclear(&(*sys).pipeline, &ft_free_pipeline);
	(*sys).lst = NULL;
	(*sys).backup = NULL;
	(*sys).pipeline = NULL;
}

int	ft_tree_routine(t_tree *root, t_sys *sys)
{
	t_list	*lst;
	t_list	*parsed;
	t_list	*backup;
	t_list	*pipeline;

	lst = parsing_init((char *)(*root).content, sys);
	parsed = ft_lstmap(lst, ft_env, free);
	backup = parsed;
	ft_wildcard(&parsed);
	pipeline = ft_pipeline_init(parsed);
	ft_reset_pipeline(sys);
	(*sys).pipeline = pipeline;
	(*sys).lst = lst;
	(*sys).backup = backup;
	if (pipeline != NULL)
	{
		if ((*(t_pipeline *)(*pipeline).content).fd_in > 0)
			dup2((*(t_pipeline *)(*pipeline).content).fd_in, 0);
		(*sys).exit_code = run(pipeline, sys);
	}
	return ((*sys).exit_code);
}

int	ft_exec_tree(t_tree *root, t_sys *sys)
{
	char	*cmd;
	int		exit_code;

	exit_code = 0;
	if (root == NULL)
		return (0);
	cmd = (*root).content;
	if (ft_strncmp(cmd, "&&", 3) && ft_strncmp(cmd, "||", 3))
		return (ft_tree_routine(root, sys));
	else if (!ft_strncmp(cmd, "&&", 3))
	{
		exit_code = 1;
		if (!ft_exec_tree((*root).left, sys))
			exit_code = ft_exec_tree((*root).right, sys);
	}
	else if (!ft_strncmp(cmd, "||", 3) && ft_exec_tree((*root).left, sys))
		exit_code = ft_exec_tree((*root).right, sys);
	return (exit_code);
}
