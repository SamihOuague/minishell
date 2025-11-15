/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouajjou <iouajjou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 17:23:18 by iouajjou          #+#    #+#             */
/*   Updated: 2024/08/29 14:17:04 by iouajjou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_sig;

int	checkcmd(t_pipeline *pipe, t_sys *sys, t_list *cmds)
{
	int	exit_value;

	exit_value = -1;
	if (pipe->argc == 0)
		return (exit_value);
	else if (!ft_strncmp(pipe->argv[0], "cd", 3))
		exit_value = cd(pipe, sys);
	else if (!ft_strncmp(pipe->argv[0], "exit", 5))
	{
		if (sys->pipe == 1 && cmds->next == NULL)
			exit_value = exit_cmd(pipe, sys);
	}
	else if (!ft_strncmp(pipe->argv[0], "export", 7))
	{
		if (cmds->next != NULL)
			return (0);
		exit_value = export(sys, pipe, 1);
	}
	else if (!ft_strncmp(pipe->argv[0], "unset", 6))
	{
		if (cmds->next != NULL)
			return (0);
		exit_value = unset(sys, pipe, 1);
	}
	return (exit_value);
}

int	ft_create_file(t_pipeline **pip)
{
	t_list	*cursor;
	t_file	*file;

	cursor = (**pip).file;
	while (cursor != NULL)
	{
		file = (*cursor).content;
		if ((*file).a_mode)
			(**pip).fd_out = open((*file).name,
					O_RDWR | O_CREAT | O_APPEND, 0644);
		else
			(**pip).fd_out = open((*file).name,
					O_RDWR | O_CREAT | O_TRUNC, 0644);
		if ((**pip).fd_out == -1)
			return (error("msh", ERR_G));
		if ((*cursor).next != NULL)
			close((**pip).fd_out);
		cursor = (*cursor).next;
	}
	return (0);
}

int	open_fd(t_pipeline *pip)
{
	t_list	*cursor;
	t_file	*file;

	cursor = (*pip).file;
	while (cursor)
	{
		file = (*cursor).content;
		if (file->io == 0)
		{
			pip->fd_in = open((*file).name, O_RDONLY);
			if (pip->fd_in == -1)
				return (error("msh:", ERR_G));
		}
		else
		{
			if (ft_create_file(&pip) != 0)
				return (ERR_G);
		}
		cursor = cursor->next;
	}
	return (0);
}

int	error_open_fd(t_list *cmds, int *pipefd, t_sys *sys)
{
	close(pipefd[1]);
	if (cmds != NULL && cmds->next != NULL)
		return (next_pipe(cmds, pipefd, sys));
	return (ERR_G);
}

int	run(t_list *cmds, t_sys *sys)
{
	t_pipeline	*pip;
	pid_t		pid;
	int			pipefd[2];
	int			exit_code;

	if (g_sig != 0)
		return (128 + g_sig);
	sys->pipe++;
	pip = (t_pipeline *)(*cmds).content;
	if (pipe(pipefd) == -1)
		return (error("pipe", ERR_G));
	if (open_fd(pip) != 0)
		return (error_open_fd(cmds, pipefd, sys));
	exit_code = checkcmd(pip, sys, cmds);
	if (exit_code != -1)
		return (cmd_invalid_here(cmds, pipefd, sys, exit_code));
	pid = fork();
	if (pid < 0)
		return (error("fork", ERR_G));
	else if (pid == 0 && cmds != NULL && (*cmds).next == NULL)
		return (last_pipe(pip, sys, pipefd));
	else if (pid == 0)
		return (child_process(pip, pipefd, sys));
	else
		return (parent_process(cmds, pipefd, sys, pid));
}
