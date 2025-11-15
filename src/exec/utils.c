/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouajjou <iouajjou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 16:31:27 by iouajjou          #+#    #+#             */
/*   Updated: 2024/07/29 13:55:07 by iouajjou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	error(char *err, int exit_code)
{
	if (exit_code == EXIT_SUCCESS || errno == EXIT_SUCCESS)
		return (exit_code);
	perror(err);
	return (exit_code);
}

void	free_splitter(char **splitter)
{
	int	i;

	i = 0;
	while (splitter[i])
	{
		free(splitter[i]);
		i++;
	}
	free(splitter);
}

int	size_array(char **array)
{
	int	i;

	if (!array)
		return (0);
	i = 0;
	while (array[i])
		i++;
	return (i);
}

void	free_pipeline(void *content)
{
	t_pipeline	*pipeline;

	pipeline = (t_pipeline *) content;
	free(pipeline->eof);
	free(pipeline);
}

char	*getname(char *var)
{
	int		i;
	int		j;
	char	*name;

	i = 0;
	while (var && var[i])
	{
		if (var[i] == '=')
			break ;
		i++;
	}
	if (i == 0)
		return (NULL);
	name = malloc(sizeof(char) * (i + 1));
	if (!name)
		return (NULL);
	j = 0;
	while (j < i)
	{
		name[j] = var[j];
		j++;
	}
	name[j] = 0;
	return (name);
}
