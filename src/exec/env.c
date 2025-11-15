/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouajjou <iouajjou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 13:04:17 by iouajjou          #+#    #+#             */
/*   Updated: 2024/08/09 15:36:53 by iouajjou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	change_env_local(t_list **local_env, char *new, char *name)
{
	t_list	*temp;
	char	*name_current;
	int		trigger;

	trigger = 0;
	temp = *local_env;
	while (*local_env)
	{
		name_current = getname((*local_env)->content);
		if (!ft_strncmp(name_current, name, ft_strlen(name)))
		{
			free((*local_env)->content);
			(*local_env)->content = new;
			trigger = 1;
		}
		free(name_current);
		*local_env = (*local_env)->next;
	}
	*local_env = temp;
	if (trigger == 0)
		ft_lstadd_front(local_env, ft_lstnew(new));
	else
		return (1);
	return (0);
}

int	change_env_var(t_pipeline *pipe, t_sys *sys, int i)
{
	char	*name_current;
	char	*name;
	char	**new_env;
	int		j;

	j = -1;
	name = getname(pipe->argv[i]);
	new_env = *sys->envp;
	while ((*sys->envp)[++j])
	{
		name_current = getname((*sys->envp)[j]);
		if (!ft_strncmp(name_current, name, ft_strlen(name) + 1))
		{
			free(name_current);
			new_env[j] = ft_strdup(pipe->argv[i]);
			if (!new_env[j])
				return (error("msh", ERR_BLT));
			change_env_local(&sys->local_env, new_env[j], name);
		}
		else
			free(name_current);
	}
	free(name);
	*sys->envp = new_env;
	return (EXIT_SUCCESS);
}

int	check_exist(t_sys *sys, t_pipeline *pipe, int i)
{
	char	*name;

	name = getname(pipe->argv[i]);
	if (getenv(name))
	{
		free(name);
		return (change_env_var(pipe, sys, i));
	}
	free(name);
	return (-1);
}

char	**get_new_env(t_sys *sys, t_pipeline *pipe, int i)
{
	char	**new_env;
	int		j;

	new_env = malloc(sizeof(char *) * (size_array(*sys->envp) + 2));
	if (!new_env)
		return (NULL);
	j = 0;
	while ((*sys->envp)[j])
	{
		new_env[j] = (*sys->envp)[j];
		j++;
	}
	new_env[j] = ft_strdup(pipe->argv[i]);
	if (!new_env[j])
		return (NULL);
	ft_lstadd_front(&(*sys).local_env, ft_lstnew(new_env[j]));
	new_env[j + 1] = NULL;
	return (new_env);
}

int	export(t_sys *sys, t_pipeline *pipe, int i)
{
	char	**new_env;

	if (!pipe->argv[i])
		return (EXIT_SUCCESS);
	if (!check_valid_export(pipe->argv[i]))
	{
		ft_putstr_fd("msh: export: `", 2);
		ft_putstr_fd(pipe->argv[i], 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		return (ERR_G);
	}
	if (!ft_strchr(pipe->argv[i], '='))
		return (EXIT_SUCCESS);
	if (check_exist(sys, pipe, i) != -1)
		return (export(sys, pipe, i + 1));
	new_env = get_new_env(sys, pipe, i);
	if (!new_env)
		return (error("msh: export", ERR_BLT));
	free(*sys->envp);
	*sys->envp = new_env;
	return (export(sys, pipe, i + 1));
}
