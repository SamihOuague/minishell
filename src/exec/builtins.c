/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouajjou <iouajjou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 17:35:47 by iouajjou          #+#    #+#             */
/*   Updated: 2024/08/16 16:01:57 by iouajjou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pwd(void)
{
	char	*output;

	if (getenv("PWD"))
		output = ft_strdup(getenv("PWD"));
	else
		output = getcwd(NULL, 0);
	if (!output)
		return (error("msh: pwd", ERR_BLT));
	printf("%s\n", output);
	free(output);
	return (EXIT_SUCCESS);
}

int	cd(t_pipeline *pipe, t_sys *sys)
{
	char	*path;
	char	*new_pwd;

	if (pipe->argc > 2)
		return (put_error("msh: cd:", NULL, "too many arguments\n"));
	if (!pipe->argv[1])
	{
		path = getenv("HOME");
		if (!path)
			return (put_error("msh: cd: ", NULL, "HOME not set"));
	}
	else
		path = pipe->argv[1];
	change_env_pwd(sys, getenv("PWD"), "OLDPWD");
	if (chdir(path) == -1)
		return (error("msh: chdir", ERR_G));
	new_pwd = getcwd(NULL, 0);
	if (change_env_pwd(sys, new_pwd, "PWD") != 0)
	{
		ft_putstr_fd("cd : error retrieving current directory:", 2);
		ft_putstr_fd(": canot access parent directories", 2);
		ft_putstr_fd(": No such file or directory\n", 2);
	}
	free(new_pwd);
	return (EXIT_SUCCESS);
}

int	echo(t_pipeline *pipe)
{
	int	i;

	i = 1;
	if (pipe->argv[1]
		&& !ft_strncmp(pipe->argv[1], "-n", 3))
		i++;
	if ((*pipe).argv[i] == NULL || pipe->argv[i][0] == 0)
	{
		if (!pipe->argv[1] || !pipe->argv[1][0] || (pipe->argv[1]
				&& ft_strncmp(pipe->argv[1], "-n", 3)))
			printf("\n");
		return (EXIT_SUCCESS);
	}
	while (pipe->argv[i + 1])
	{
		ft_putstr_fd(pipe->argv[i], pipe->fd_out);
		if (ft_strncmp(pipe->argv[i], "", 2))
			ft_putstr_fd(" ", pipe->fd_out);
		i++;
	}
	ft_putstr_fd(pipe->argv[i], pipe->fd_out);
	if (!pipe->argv[1] || (pipe->argv[1]
			&& ft_strncmp(pipe->argv[1], "-n", 3)))
		ft_putstr_fd("\n", pipe->fd_out);
	return (EXIT_SUCCESS);
}

int	env(t_pipeline *pipe, t_sys *sys)
{
	int	i;

	i = 0;
	while ((*sys->envp)[i])
	{
		ft_putstr_fd((*sys->envp)[i], pipe->fd_out);
		ft_putchar_fd('\n', pipe->fd_out);
		i++;
	}
	return (EXIT_SUCCESS);
}

int	exit_cmd(t_pipeline *pipe, t_sys *sys)
{
	size_t	i;
	int		exit_code;

	i = 0;
	if (!pipe->argv[1])
		exit(0 * end_shell(sys));
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
			exit(ERR_BLT * end_shell(sys));
		}
		i++;
	}
	if (pipe->argv[1] && pipe->argv[2])
		return (ERR_G * put_error("msh: exit: ", "", "too many arguments"));
	exit((char)exit_code * end_shell(sys));
}
