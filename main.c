/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouajjou <iouajjou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 10:21:30 by iouajjou          #+#    #+#             */
/*   Updated: 2024/08/29 17:24:51 by iouajjou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "ast.h"

int	g_sig = 0;

int	ft_errors_checker(t_sys *sys)
{
	int		i;
	int		b;

	i = 0;
	b = 0;
	if (!ft_isbalanced((*sys).input))
		return (1);
	if (!ft_check_tree((*sys).root, sys))
		return (1);
	if (!ft_io_syntax(sys, &i, &b))
		return (1);
	return (0);
}

int	ft_exec_pipeline(t_sys *sys)
{
	t_tree	*root;
	char	*tmp;
	int		exit_code;

	exit_code = 127;
	tmp = ft_strtrim(sys->input, " ");
	if (*tmp == '\0')
		return (0);
	root = ft_tree_new(tmp);
	ft_str_to_tree(&root);
	(*sys).root = root;
	if (ft_errors_checker(sys))
	{
		(*sys).root = root;
		free_all(sys);
		ft_putstr_fd("Syntax Error\n", 2);
		return (2);
	}
	exit_code = ft_exec_tree(root, sys);
	free_all(sys);
	return (exit_code);
}

char	*get_prompt(void)
{
	return ("\033[1;34mminishell$> \033[0m");
}

int	ft_minishell_routine(t_sys *sys)
{
	char		*prompt;

	signal(SIGINT, handler_sigusr);
	signal(SIGQUIT, SIG_IGN);
	g_sig = 0;
	prompt = get_prompt();
	free(sys->input);
	sys->input = readline(prompt);
	if (!sys->input)
		return (0);
	if (sys->input[0])
	{
		add_history(sys->input);
		sys->pipe = 0;
		sys->exit_code = ft_exec_pipeline(sys);
	}
	return (1);
}

int	main(void)
{
	extern char	**environ;
	t_sys		*sys;

	sys = init_sys(&environ);
	if (!sys->envp)
		return (error("msh", ERR_BLT));
	while (ft_minishell_routine(sys))
		;
	end_shell(sys);
	printf("exit\n");
	return (0);
}
