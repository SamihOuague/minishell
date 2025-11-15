/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouajjou <iouajjou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 12:09:26 by iouajjou          #+#    #+#             */
/*   Updated: 2024/06/14 12:57:48 by iouajjou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_top(t_list **local_env, char *search)
{
	char	*find;
	t_list	*top;

	find = getname((*local_env)->content);
	if (!find)
		return (-1);
	if (!ft_strncmp(find, search, ft_strlen(search) + 1))
	{
		top = (*local_env)->next;
		ft_lstdelone(*local_env, free);
		*local_env = top;
		free(find);
		return (1);
	}
	free(find);
	return (0);
}

int	check_all(t_list **local_env, char *search, t_list	*prev)
{
	char	*find;

	while (*local_env)
	{
		find = getname((*local_env)->content);
		if (!find)
			return (0);
		if (!ft_strncmp(find, search, ft_strlen(search) + 1))
		{
			prev->next = (*local_env)->next;
			ft_lstdelone(*local_env, free);
			free(find);
			return (1);
		}
		else
			prev = *local_env;
		free(find);
		*local_env = (*local_env)->next;
	}
	return (1);
}

int	delete_local_env(t_list **local_env, char *search)
{
	t_list	*prev;
	t_list	*top;
	int		value;

	if (!local_env || !(*local_env))
		return (1);
	prev = *local_env;
	value = check_top(local_env, search);
	if (value == 1)
		return (1);
	if (value == -1)
		return (0);
	top = *local_env;
	*local_env = (*local_env)->next;
	value = 1;
	value = check_all(local_env, search, prev);
	*local_env = top;
	return (value);
}

static	char	**reduce_env(t_sys *sys, char *search)
{
	int		j;
	int		k;
	char	*find;
	char	**new_env;

	new_env = malloc(sizeof(char *) * (size_array(*sys->envp)));
	if (!new_env)
		return (NULL);
	j = -1;
	k = 0;
	while ((*sys->envp)[++j] != NULL)
	{
		find = getname((*sys->envp)[j]);
		if (!find)
		{
			new_env[k] = NULL;
			free_splitter(new_env);
			return (NULL);
		}
		if (ft_strncmp(find, search, ft_strlen(search) + 1))
			new_env[k++] = (*sys->envp)[j];
		free(find);
	}
	new_env[k] = NULL;
	return (new_env);
}

int	unset(t_sys *sys, t_pipeline *pipe, int i)
{
	char	**new_env;

	if (!pipe->argv[i])
		return (EXIT_SUCCESS);
	new_env = reduce_env(sys, pipe->argv[i]);
	if (!new_env)
		return (error("msh: unset", ERR_BLT));
	free(*sys->envp);
	*sys->envp = new_env;
	if (delete_local_env(&sys->local_env, pipe->argv[i]) == 0)
		return (error("msh: unset", ERR_BLT));
	return (unset(sys, pipe, i + 1));
}
