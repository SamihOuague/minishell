/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaguen <souaguen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 01:24:00 by  souaguen         #+#    #+#             */
/*   Updated: 2024/03/19 04:02:53 by souaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>


char	*set_exec(char *cmd)
{
	char	**path;
	char	*abs_path;
	char	*tmp;
	int		i;

	i = 0;
	path = ft_split(getenv("PATH"), ':');
	abs_path = ft_strdup(cmd);
	while (path[i] != NULL)
	{
		if (access(abs_path, X_OK) == 0)
			return (abs_path);
		free(abs_path);
		tmp = ft_strjoin(path[i], "/");
		abs_path = ft_strjoin(tmp, cmd);
		free(tmp);
		i++;
	}
	free(abs_path);
	return (cmd);
}

int	exec_cmd(char **argv, char **envp)
{
	pid_t	pid;
	int		wstatus;

	pid = fork();
	if (pid < 0)
		return (-1);
	else if (pid == 0)
	{
		argv[0] = set_exec(argv[0]);
		execve(argv[0], argv, envp);
		perror("execve");
		exit(EXIT_FAILURE);
	}
	else
	{
		waitpid(-1, &wstatus, 0);
		return (WEXITSTATUS(wstatus));
	}
}

void	read_file(int fd, int fd_out)
{
	char	buf;

	while (read(fd, &buf, 1) > 0)
		ft_putchar_fd(buf, fd_out);
}

t_list	*get_cmds(char *str)
{
	t_list	*lst;
	t_list	*pipeline;
	t_list	*cursor;
	char		*tmp;

	lst = remove_quotes(str);	
	pipeline = get_pipeline(lst);
	cursor = pipeline;
	while (cursor != NULL)
	{
		tmp = (*cursor).content;
		(*cursor).content = ft_split((*cursor).content, ' ');
		free(tmp);
		cursor = (*cursor).next;
	}
	ft_lstclear(&lst, &free);
	return (pipeline);
}

int	run(t_list *cmds, char **envp)
{
	pid_t	pid;
	int		pipefd[2];
	int		wstatus;
	int		fd;	
	int		tty_fd;

	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		close(pipefd[0]);
		fd = dup(1);
		dup2(pipefd[1], 1);
		exec_cmd((*cmds).content, envp);
		dup2(fd, 1);
		close(pipefd[1]);
		close(fd);
		exit(EXIT_SUCCESS);
	}
	else
	{
		close(pipefd[1]);	
		if (cmds != NULL && (*cmds).next != NULL)
		{
			fd = dup(0);
			dup2(pipefd[0], 0);
			run((*cmds).next, envp);
			dup2(fd, 0);
			close(fd);
		}
		else
			read_file(pipefd[0], fd);
		waitpid(-1, &wstatus, 0);
		close(pipefd[0]);
		return (WEXITSTATUS(wstatus));
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_list	*lst;
	t_list	*cursor;
	char		*command;
	int		exit_status;
	
	lst = NULL;
	command = readline("Minishell $> ");
	while (command != NULL && ft_strncmp(command, "exit", 5))
	{
		
		lst = get_cmds(command);
		exit_status = run(lst, envp);
		add_history(command);
		free(command);
		command = readline("Minishell $> ");
	}
	free(command);
	return (0);
}
