/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaguen <souaguen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 21:47:13 by  souaguen         #+#    #+#             */
/*   Updated: 2024/03/09 13:28:36 by souaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include <unistd.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <wait.h>
#include <sys/ioctl.h>

char	**ft_super_split(char *str, char c)
{
	char	**spl;
	int		i;
	int		count;
	int		q;

	i = 0;
	count = 0;
	while (*(str + i) == c && *(str + i) != '\0')
		i++;
	while (*(str + i) != '\0')
	{
		if (*(str + i) == '\"')
		{
			while (*(str + i) != '\"' && *(str + i) != '\0')
				i++;
		}
		else if (*(str + i) == c && (*(str + (i + 1)) != c && *(str + (i + 1)) != '\0'))
			count++;
		if (*(str + i) != '\0')
			i++;
	}
	spl = malloc(sizeof(char *) * (count + 2));
	spl[count + 1] = NULL;
	i = 0;
	while (*(str + i) == c && *(str + i) != '\0')
		i++;
	spl[0] = (str + i);
	count = 1;
	q = 0;
	while (*(str + i) != '\0')
	{
		if (*(str + i) == '\"')
		{
			spl[count] = (str + i);
			count++;
			i++;
			while (*(str + i) != '\"' && *(str + i) != '\0')
				i++;
			if (*(str + i) == '\"')
				i++;
			else if (*(str + i) == '\0')
				return (spl);
		}
		else if (*(str + i) == c)
		{
			while (*(str + i) == c)
			{
				*(str + i) = '\0';
				i++;
 				if (*(str + i) == '\0')
					return (spl);
			}
			if (*(str + i) != '\"')
			{
				spl[count] = (str + i); 
				count++;
			}
		}
		if (*(str + i) != '\"' && *(str + i) != c)
			i++;
	}
	return (spl);
}

char	**ft_pipe_split(char *str, char c)
{
	char	**spl;
	int		i;
	int		count;
	int		q;

	i = 0;
	count = 0;
	while (*(str + i) == c && *(str + i) != '\0')
		i++;
	while (*(str + i) != '\0')
	{
		if (*(str + i) == c && (*(str + (i + 1)) != c && *(str + (i + 1)) != '\0'))
			count++;
		if (*(str + i) != '\0')
			i++;
	}
	spl = malloc(sizeof(char *) * (count + 2));
	spl[count + 1] = NULL;
	i = 0;
	while (*(str + i) == c && *(str + i) != '\0')
		i++;
	spl[0] = (str + i);
	count = 1;
	q = 0;
	while (*(str + i) != '\0')
	{
		if (*(str + i) == c)
		{
			while (*(str + i) == c)
			{
				*(str + i) = '\0';
				i++;
 				if (*(str + i) == '\0')
					return (spl);
			}
			spl[count] = (str + i); 
			count++;
		}
		i++;
	}
	return (spl);
}

char	*set_exec(char *cmd)
{
	char	**path;
	char	*abs_path;
	char	*tmp;
	int		i;

	i = 0;
	path = ft_pipe_split(getenv("PATH"), ':');
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

int	run(t_list *cmds, char **envp)
{
	pid_t	pid;
	int		pipefd[2];
	int		wstatus;
	int		fd;

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
			waitpid(-1, &wstatus, 0);
			dup2(fd, 0);
			close(fd);
		}
		else
			read_file(pipefd[0], 1);	
		return (WEXITSTATUS(wstatus));
	}
}

char	**ft_set_cmds(t_list **lst, char *cmd)
{
	char	**spl;
	int		i;

	i = -1;
	spl = ft_pipe_split(cmd, '|');
	while (spl[(++i)] != NULL)	
		ft_lstadd_back(lst, ft_lstnew(ft_super_split(spl[i], ' ')));
	return (spl);
}

int	main(int argc, char **argv, char **envp)
{
	char	**spl;	
	char	*str;
	t_list	*cmds;
	int		i;
	pid_t		pid;
	char		buf;
	int		fd;

	i = 0;
	cmds = NULL;
	str = readline("Minishell $> ");	
	while (ft_strncmp(str, "exit", 5))
	{
		add_history(str);
		if (str != NULL && str[0] != '\0')
		{	
			spl = ft_set_cmds(&cmds, str);
			pid = run(cmds, envp);
			ft_lstclear(&cmds, free);	
			free(spl);
		}
		free(str);
		rl_on_new_line();
		str = readline("Minishell $> ");
	}
	free(str);
	rl_clear_history();
	return (0);	
}
