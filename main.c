/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaguen <souaguen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 21:47:13 by  souaguen         #+#    #+#             */
/*   Updated: 2024/03/11 05:13:55 by souaguen         ###   ########.fr       */
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
			dup2(fd, 0);
			close(fd);
		}
		else
			read_file(pipefd[0], 1);	
		close(pipefd[0]);
		waitpid(-1, &wstatus, 0);
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

int	count_vars(char *str)
{
	int	i;
	int	c;

	i = 0;
	c = 0;
	while (*(str + i) != '\0')
	{
		if (*(str + i) == '$')
			c++;
		i++;
	}
	return (c);
}

char	*var_to_str(char *str)
{
	char	*tmp;
	char	*new_str;
	char	**vars;
	char	**spl;
	t_list	*n_str;
	t_list	*cursor;
	int		i;
	int		j;
	int		k;
	long		n;

	n_str = NULL;
	if (ft_strchr(str, '$') == NULL)
		return (str);
	j = count_vars(str) + 1;
	vars = malloc(sizeof(char *) * j);
	vars[j - 1] = NULL;
	i = 0;
	j = 0;
	new_str = NULL;
	while (*(str + i) != '\0')
	{
		if (*(str + i) == '$')
		{
			n = i + 1;
			k = 0;
			while (*(str + n) != '\0')
			{
				if (ft_strchr(" $", *(str + n)))
					break ;
				n++;
				k++;
			}
			vars[j] = malloc(sizeof(char) * (k + 1));
			ft_memcpy(vars[j], (str + i + 1), k + 1);
			vars[j][k] = '\0';
			j++;
		}
		if (*(str + i) != '\0')
			i++;
	}
	j = 0;
	while (vars[j] != NULL)
	{
		new_str = getenv(vars[j]);
		free(vars[j]);
		vars[j] = new_str;
		j++;
	}
	
	i = 0;
	new_str = str;
	j = 0;
	while (*(str + i) != '\0')
	{
		if (*(str + i) == '$')
		{
			*(str + i) = '\0';
			ft_lstadd_back(&n_str, ft_lstnew(ft_strdup(str)));
			ft_lstadd_back(&n_str, ft_lstnew(vars[j]));
			while (*(str + i + 1) != '\0' && *(str + i + 1) != ' ' && *(str + i + 1) != '$')
				i++;
			str = (str + i + 1);
			i = -1;
			j++;	
		}
		i++;
	}
	new_str = ft_strdup("");
	if (str != NULL)
		ft_lstadd_back(&n_str, ft_lstnew(str));
	cursor = n_str;
	while (cursor != NULL)
	{
		if ((*cursor).content != NULL)
		{
			tmp = new_str;
			new_str = ft_strjoin(new_str, (char *)(*cursor).content);
			free(tmp);
		}
		cursor = (*cursor).next;
	}
	return (new_str);
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
		str = var_to_str(str);
		add_history(str);
		if (str != NULL && str[0] != '\0')
		{	
			spl = ft_set_cmds(&cmds, str);
			if (spl[1] != NULL)
				pid = run(cmds, envp);
			else
				pid = exec_cmd((*cmds).content, envp);
			ft_lstclear(&cmds, free);
			free(spl);
		}
		free(str);
		str = readline("Minishell $> ");
	}
	free(str);
	rl_clear_history();
	return (0);	
}
