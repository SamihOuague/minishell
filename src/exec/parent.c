/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouajjou <iouajjou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 15:02:06 by iouajjou          #+#    #+#             */
/*   Updated: 2024/08/29 15:41:08 by iouajjou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	last_pipe(t_pipeline *pip, t_sys *sys, int pipefd[2])
{
	int	exit_code;

	signal(SIGINT, handler_child_sigusr);
	signal(SIGQUIT, handler_sigquit);
	close(pipefd[0]);
	close(pipefd[1]);
	pipefd[0] = dup(0);
	pipefd[1] = dup(1);
	if ((*pip).fd_in != 0)
		dup2((*pip).fd_in, 0);
	if ((*pip).fd_out != 1)
		dup2((*pip).fd_out, 1);
	exit_code = exec(pip, sys);
	dup2(pipefd[0], 0);
	dup2(pipefd[1], 1);
	close(pipefd[0]);
	close(pipefd[1]);
	if ((*pip).fd_out != 1)
		close((*pip).fd_out);
	if ((*pip).fd_in != 0)
		close((*pip).fd_in);
	end_shell(sys);
	exit(exit_code);
}

int	next_pipe(t_list *cmds, int pipefd[], t_sys *sys)
{
	int			fd[1];
	t_pipeline	*pipe;
	int			exit_code;

	fd[0] = dup(0);
	if (!fd[0])
		return (error("dup", ERR_G));
	ft_lstadd_back(&sys->fds, ft_lstnew(fd));
	pipe = (t_pipeline *)(*(*cmds).next).content;
	if (pipe->fd_in != 0)
	{
		if (dup2(pipe->fd_in, 0) == -1)
			return (error("dup2", ERR_G));
	}
	else
	{
		if (dup2(pipefd[0], 0) == -1)
			return (error("dup2", ERR_G));
		close(pipefd[0]);
	}
	exit_code = run((*cmds).next, sys);
	if (dup2(fd[0], 0) == -1)
		return (error("dup2", ERR_G));
	close(fd[0]);
	return (exit_code);
}

int	parent_process(t_list *cmds, int pipefd[], t_sys *sys, int pid)
{
	int			wstatus;
	int			exit_code;
	t_pipeline	*pipe;

	signal(SIGINT, handler_parent_sigusr);
	exit_code = -1;
	pipe = (t_pipeline *) cmds->content;
	if (close(pipefd[1]) == -1)
		return (error("close", ERR_G));
	if (cmds != NULL && (*cmds).next != NULL)
		exit_code = next_pipe(cmds, pipefd, sys);
	else
		read_file(pipefd[0], pipe->fd_out);
	if (waitpid(pid, &wstatus, 0) == -1)
	{
		if (errno == EINTR)
			return (error("waitpid", 128 + WTERMSIG(wstatus)));
		return (error("waitpid", ERR_G));
	}
	if (exit_code != -1)
		return (exit_code);
	return (WEXITSTATUS(wstatus));
}
