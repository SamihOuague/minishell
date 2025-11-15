/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouajjou <iouajjou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 16:29:13 by iouajjou          #+#    #+#             */
/*   Updated: 2024/08/29 16:49:31 by souaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_sig;

void	handler_sigquit(int sig)
{
	t_sys	*sys;

	(void) sig;
	sys = get_sys();
	printf("Quit (core dumped)\n");
	end_shell(sys);
	exit(131);
}

void	handler_sigusr(int sig)
{
	t_sys	*sys;

	(void) sig;
	g_sig = 0;
	sys = get_sys();
	sys->exit_code = 130;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 1);
	rl_redisplay();
}

void	handler_child_sigusr(int sig)
{
	t_sys	*sys;

	g_sig = sig;
	sys = get_sys();
	end_shell(sys);
	exit(130);
}

void	handler_parent_sigusr(int sig)
{
	(void) sig;
	g_sig = 0;
	printf("\n");
}

void	handler_here_doc_sigusr(int sig)
{
	g_sig = sig;
	close(0);
	printf("\n");
}
