/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouajjou <iouajjou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 14:59:23 by iouajjou          #+#    #+#             */
/*   Updated: 2024/08/29 14:32:33 by iouajjou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	open_fd_child(t_pipeline *pip, int pipefd[2])
{
	int	fd;

	if (close(pipefd[0]) == -1)
		return (-1);
	fd = dup(1);
	if (!fd)
		return (-1);
	if ((*pip).fd_out != 1)
	{
		if (dup2((*pip).fd_out, 1) == -1)
			return (-1);
	}
	else
	{
		if (dup2(pipefd[1], 1) == -1)
			return (-1);
	}
	if ((*pip).fd_in != 0)
	{
		if (dup2((*pip).fd_in, 0) == -1)
			return (-1);
	}
	return (fd);
}

int	close_fd_child(t_pipeline *pip, int pipefd[2], int fd)
{
	if (dup2(fd, 1) == -1)
		return (error("dup2", ERR_G));
	if (close(pipefd[1]) == -1)
		return (error("close", ERR_G));
	if (close(fd) == -1)
		return (error("close", ERR_G));
	if ((*pip).fd_out != 1)
	{
		if (close((*pip).fd_out) == -1)
			return (error("close", ERR_G));
	}
	if ((*pip).fd_in != 0)
	{
		if (close((*pip).fd_in) == -1)
			return (error("close", ERR_G));
	}
	return (EXIT_SUCCESS);
}

int	child_process(t_pipeline *pip, int pipefd[2], t_sys *sys)
{
	int	fd;
	int	exit_code;

	signal(SIGINT, handler_child_sigusr);
	signal(SIGQUIT, handler_sigquit);
	fd = open_fd_child(pip, pipefd);
	if (fd == -1)
		exit(error("msh", ERR_G));
	exit_code = exec(pip, sys);
	if (close_fd_child(pip, pipefd, fd))
		exit(error("msh", ERR_G));
	end_shell(sys);
	exit(exit_code);
}
