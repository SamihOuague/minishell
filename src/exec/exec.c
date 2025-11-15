/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouajjou <iouajjou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 15:23:58 by iouajjou          #+#    #+#             */
/*   Updated: 2024/08/09 15:16:47 by iouajjou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_check_file_status(char **argv)
{
	char	*tmp;
	char	**path;
	int		i;

	if (access(argv[0], X_OK) == 0)
		return (0);
	tmp = getenv("PATH");
	if (tmp == NULL)
		return (put_error("msh: ", argv[0], ": command not found") * ERR_NF);
	path = ft_split(tmp, ':');
	i = -1;
	while (path[(++i)] != NULL)
	{
		ft_join_free(&tmp, argv, path[i]);
		if (tmp == NULL)
			return (put_error("msh: ", argv[0], ": command not found")
				* ERR_NF);
		if (access(tmp, X_OK) == 0)
			return (ft_new_argv(tmp, argv, path));
		free(tmp);
	}
	free_splitter(path);
	return (put_error("msh: ", argv[0], ": command not found") * ERR_NF);
}

char	**new_env(void)
{
	char	**nenvp;

	nenvp = malloc(sizeof(char *) * 6);
	if (nenvp == NULL)
		return (NULL);
	if (getenv("PATH") == NULL || getenv("TERM") == NULL || !getenv("PWD")
		|| !getenv("OLDPWD") || !getenv("HOME"))
	{
		free(nenvp);
		return (NULL);
	}
	nenvp[0] = ft_strjoin("PATH=", getenv("PATH"));
	nenvp[1] = ft_strjoin("TERM=", getenv("TERM"));
	nenvp[2] = ft_strjoin("PWD=", getenv("PWD"));
	nenvp[3] = ft_strjoin("OLDPWD=", getenv("OLDPWD"));
	nenvp[4] = ft_strjoin("HOME=", getenv("HOME"));
	nenvp[5] = NULL;
	return (nenvp);
}

void	child_execve(t_pipeline *pipe, t_sys *sys)
{
	char	**envp;
	int		exit_code;

	signal(SIGINT, handler_child_sigusr);
	exit_code = EXIT_SUCCESS;
	if (pipe->argc == 0)
		exit(exit_code);
	else if (!ft_strncmp(pipe->argv[0], "./", 2)
		|| !ft_strncmp(pipe->argv[0], "/", 1))
	{
		envp = new_env();
		if (execve(pipe->argv[0], pipe->argv, envp) == -1)
			exit_code = execve_error(pipe->argv[0]);
	}
	else
	{
		envp = new_env();
		if (ft_strncmp((*pipe).argv[0], "", 2) != 0)
			exit_code = ft_check_file_status((*pipe).argv);
		if (exit_code == 0 && execve((*pipe).argv[0], (*pipe).argv, envp) == -1)
			exit_code = execve_error(pipe->argv[0]);
	}
	free_envp(envp);
	end_shell(sys);
	exit(exit_code);
}

int	exec_others(t_pipeline *pipe, t_sys *sys)
{
	int		pid;
	int		wstatus;

	pid = fork();
	wstatus = 0;
	if (pid == -1)
		return (error("msh", ERR_G));
	else if (!pid)
		child_execve(pipe, sys);
	else
	{
		if (waitpid(pid, &wstatus, 0) == -1)
		{
			if (errno == EINTR)
				return (error("msh", 128 + WTERMSIG(wstatus)));
			return (error("msh", ERR_G));
		}
	}
	if (WIFSIGNALED(wstatus))
		return (error("msh", 128 + WTERMSIG(wstatus)));
	return (WEXITSTATUS(wstatus));
}

int	exec(t_pipeline *pipe, t_sys *sys)
{
	if (pipe->argc == 0)
		pipe->exit_code = 0;
	else if (!ft_strncmp(pipe->argv[0], "pwd", 4))
		pipe->exit_code = pwd();
	else if (!ft_strncmp(pipe->argv[0], "cd", 3))
		pipe->exit_code = cd(pipe, sys);
	else if (!ft_strncmp(pipe->argv[0], "echo", 5))
		pipe->exit_code = echo(pipe);
	else if (!ft_strncmp(pipe->argv[0], "env", 4))
		pipe->exit_code = env(pipe, sys);
	else if (!ft_strncmp(pipe->argv[0], "export", 7))
		pipe->exit_code = export(sys, pipe, 1);
	else if (!ft_strncmp(pipe->argv[0], "unset", 6))
		pipe->exit_code = unset(sys, pipe, 1);
	else if (!ft_strncmp(pipe->argv[0], "exit", 5))
		pipe->exit_code = exit_without_exit(pipe, sys);
	else
		pipe->exit_code = exec_others(pipe, sys);
	return (pipe->exit_code);
}
