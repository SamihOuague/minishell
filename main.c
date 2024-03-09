/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaguen <souaguen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 21:47:13 by  souaguen         #+#    #+#             */
/*   Updated: 2024/03/09 07:05:28 by souaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <wait.h>
#include "libft/libft.h"

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

int	exec_cmd(char **argv, char **envp)
{
	pid_t	pid;
	int		wstatus;

	pid = fork();
	if (pid < 0)
		return (-1);
	else if (pid == 0)
	{
		execve(argv[0], argv, envp);
		perror("execve");
		free(argv);
		exit (EXIT_FAILURE);
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
		dup2(pipefd[1], 1);
		exec_cmd((*cmds).content, envp);
		close(pipefd[1]);
		return (EXIT_SUCCESS);
	}
	else
	{
		close(pipefd[1]);
		dup2(pipefd[0], 0);
		if (cmds != NULL && (*cmds).next != NULL)
		{
			close(pipefd[0]);
			run((*cmds).next, envp);
		}
		else
			read_file(pipefd[0], 1);
		waitpid(-1, &wstatus, 0);
		return (WEXITSTATUS(wstatus));
	}
}

int	main(int argc, char **argv, char **envp)
{
	char	**spl;
	t_list	*cmds;
	int		i;

	i = 0;
	cmds = NULL;
	if (argc != 2)
		return (1);
	spl = ft_pipe_split(argv[1], '|');
	while (spl[i] != NULL)
	{
		ft_lstadd_back(&cmds, ft_lstnew(ft_super_split(spl[i], ' ')));
		i++;
	}
	run(cmds, envp);
	ft_lstclear(&cmds, free);
	free(spl);
	return (0);
}
