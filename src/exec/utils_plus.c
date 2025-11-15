/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_plus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouajjou <iouajjou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 13:45:59 by iouajjou          #+#    #+#             */
/*   Updated: 2024/07/29 17:01:55 by iouajjou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cmd_invalid_here(t_list *cmds, int *pipefd, t_sys *sys, int exit_code)
{
	close(pipefd[0]);
	close(pipefd[1]);
	if (cmds != NULL && cmds->next != NULL)
		return (next_pipe(cmds, pipefd, sys));
	return (exit_code);
}

int	exit_without_exit(t_pipeline *pipe, t_sys *sys)
{
	size_t	i;
	int		exit_code;

	i = 0;
	if (!pipe->argv[1])
		return (0);
	if (pipe->argv[1] && pipe->argv[2])
		return (ERR_G * put_error("msh: exit: ", "", "too many arguments"));
	if (sys->pipe == 1)
		ft_putstr_fd("exit\n", pipe->fd_out);
	exit_code = ft_atoi(pipe->argv[1]);
	if (pipe->argv[1][i] == '+' || pipe->argv[1][i] == '-')
		i++;
	while (pipe->argv[1][i])
	{
		if (!ft_isdigit(pipe->argv[1][i]))
		{
			put_error("msh: exit: ", pipe->argv[1],
				": numeric argument required");
			exit_code = ERR_BLT;
			break ;
		}
		i++;
	}
	return ((char) exit_code);
}

int	check_valid_export(char *input)
{
	int	trigger;
	int	j;

	trigger = 0;
	j = 0;
	while (input[j] && input[j] != '=')
	{
		if (ft_isalpha(input[j]))
			trigger = 1;
		if (!ft_isalnum(input[j]) || input[j] == '_')
			return (0);
		j++;
	}
	if (ft_strchr(input, '=') == input)
		return (0);
	if (trigger == 0)
		return (0);
	return (1);
}

int	put_error(char *cmd, char *arg, char *error)
{
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(error, 2);
	ft_putstr_fd("\n", 2);
	return (1);
}
