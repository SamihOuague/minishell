/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   system.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouajjou <iouajjou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 14:04:21 by iouajjou          #+#    #+#             */
/*   Updated: 2024/08/29 15:03:00 by iouajjou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_envp(char **envp)
{
	int	i;

	i = 0;
	while (envp && envp[i])
	{
		free(envp[i]);
		envp[i] = NULL;
		i++;
	}
	free(envp);
	envp = NULL;
}

char	***get_envp(char ***environ)
{
	char	**envp;
	int		i;

	envp = ft_calloc(sizeof(char *), size_array(*environ) + 1);
	if (!envp)
		return (NULL);
	i = 0;
	while (environ && *environ && (*environ)[i])
	{
		envp[i] = ft_strdup((*environ)[i]);
		if (!envp[i])
		{
			free_envp(envp);
			return (NULL);
		}
		i++;
	}
	envp[i] = NULL;
	*environ = envp;
	return (environ);
}

t_sys	*init_sys(char ***envp)
{
	t_sys	*sys;

	sys = get_sys();
	sys->input = NULL;
	sys->root = NULL;
	sys->lst = NULL;
	sys->backup = NULL;
	sys->pipeline = NULL;
	sys->local_env = NULL;
	sys->fds = NULL;
	sys->exit_code = 0;
	sys->envp = get_envp(envp);
	if (!sys->envp)
		exit(error("msh", ERR_G));
	sys->envp_backup = *sys->envp;
	return (sys);
}

t_sys	*get_sys(void)
{
	static t_sys	sys;

	return (&sys);
}
