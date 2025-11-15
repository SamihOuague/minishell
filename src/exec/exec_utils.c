/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouajjou <iouajjou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 10:16:28 by souaguen          #+#    #+#             */
/*   Updated: 2024/08/09 14:01:39 by iouajjou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_directory(const char *path)
{
	struct stat	path_stat;

	stat(path, &path_stat);
	return (S_ISDIR(path_stat.st_mode));
}

int	change_env_pwd(t_sys *sys, char *new_pwd, char *var)
{
	int		i;
	char	*name;

	i = -1;
	if (!new_pwd)
		return (ERR_G);
	while (*sys->envp && (*sys->envp)[++i])
	{
		name = getname((*sys->envp)[i]);
		if (!ft_strncmp(name, var, ft_strlen(var) + 1))
		{
			free(name);
			name = ft_strjoin(var, "=");
			if (!name)
				return (error("msh: cd", ERR_BLT));
			(*sys->envp)[i] = ft_strjoin(name, new_pwd);
			free(name);
			if (!(*sys->envp)[i])
				return (error("msh: cd", ERR_BLT));
			change_env_local(&sys->local_env, (*sys->envp)[i], var);
		}
		else
			free(name);
	}
	return (EXIT_SUCCESS);
}

int	execve_error(const char *path)
{
	if (!path || !path[0])
		return (0);
	if (access(path, F_OK) != 0)
	{
		put_error("msh: ", (char *)path, ": No such file or directory\n");
		return (ERR_NF);
	}
	else if ((!ft_strncmp(path, "./", 2) || !ft_strncmp(path, "/", 1))
		&& is_directory(path))
	{
		put_error("msh: ", (char *)path, ": Is a directory\n");
		return (ERR_EXEC);
	}
	else if (access(path, X_OK) != 0)
	{
		put_error("msh: ", (char *)path, ": Permission denied\n");
		return (ERR_EXEC);
	}
	else
	{
		put_error("msh: ", (char *)path, ": command not found\n");
		return (ERR_NF);
	}
}

void	ft_join_free(char **ptr, char **argv, char *str)
{
	char	*tmp;

	*ptr = NULL;
	tmp = ft_strjoin(str, "/");
	*ptr = ft_strjoin(tmp, argv[0]);
	free(tmp);
}

int	ft_new_argv(char *str, char **argv, char **path)
{
	free(argv[0]);
	argv[0] = str;
	free_splitter(path);
	return (0);
}
